import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Symbols of companies user has bought stocks from
    owned_shares = db.execute(
        "SELECT symbol, shares FROM wallets WHERE person_id = ? GROUP BY symbol ORDER BY shares DESC", session["user_id"])

    # User's available cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    # User's total holdings
    total_holdings = 0
    for company in owned_shares:
        total_holdings = total_holdings + lookup(company["symbol"])["price"] * company["shares"]

    return render_template("index.html", owned_shares=owned_shares, total_holdings=total_holdings, lookup=lookup, usd=usd, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Input variables
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        quote = lookup(symbol)

        # Ensure symbol is in database
        if not quote:
            return apology("invalid symbol", 400)

        # Ensure user inputs valid share amount
        if not shares.isdigit() or int(shares) <= 0:
            return apology("invalid amount of shares", 400)

        # Calculate due payment
        payment = quote["price"] * int(shares)

        # User's balance before purchase
        b_balance_list = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        b_balance = b_balance_list[0]["cash"]

        # User's balance after purchase
        a_balance = b_balance - payment

        # User's shares before sale
        owned_shares_list = db.execute("SELECT shares FROM wallets WHERE person_id = ? AND symbol = ?", session["user_id"], symbol)
        if not owned_shares_list:
            owned_shares = 0
        else:
            owned_shares = float(owned_shares_list[0]["shares"])

        # User's shares after sale
        owned_shares = owned_shares + int(shares)

        # Ensure user has enough cash
        if a_balance < 0:
            return apology("purchase declined - insufficient funds", 400)

        # Update user's balance after purchase
        new_balance = db.execute("UPDATE users SET cash=? WHERE id=?", a_balance, session["user_id"])

        # Add purchase to purchases database
        new_purchase = db.execute("INSERT INTO purchases (person_id, symbol, price, shares, transaction_type) VALUES (?, ?, ?, ?, ?)",
                                  session["user_id"], symbol, quote["price"], shares, "BUY")

        # Add purchase to wallet
        symbol_in_wallet = db.execute("SELECT shares FROM wallets WHERE person_id = ? AND symbol = ?", session["user_id"], symbol)
        if not symbol_in_wallet:
            addto_wallet = db.execute("INSERT INTO wallets (person_id, shares, symbol) VALUES (?, ?, ?)",
                                      session["user_id"], owned_shares, symbol)
        else:
            addto_wallet = db.execute("UPDATE wallets SET shares = ? WHERE person_id = ? AND symbol = ?",
                                      owned_shares, session["user_id", symbol])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT transaction_type, symbol, shares, price, time FROM purchases WHERE person_id = ?", session["user_id"])

    return render_template("history.html", transactions=transactions, lookup=lookup, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get information of symbol from database
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # Make sure symbol exists
        if not quote:
            return apology("invalid symbol", 400)

        # Variables for the html template
        quote_symbol = quote["symbol"]
        quote_price = usd(quote["price"])

        # Render template with symbol information
        return render_template("quoted.html", quote=quote, quote_symbol=quote_symbol, quote_price=quote_price)

    # If user accesses route via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Data variables
    username = request.form.get("username")
    password = request.form.get("password")
    existing_usernames = db.execute("SELECT username FROM users")
    # Transform list of dicts into list
    existing_usernames_list = [d['username'] for d in existing_usernames]

    # If user fills form
    if request.method == "POST":
        # Ensure username was submited
        if not request.form.get("username"):
            return apology("most provide username", 400)

        # Ensure username is available
        elif request.form.get("username") in existing_usernames_list:
            return apology("username is not available", 400)

        # Ensure password was submited
        elif not request.form.get("password"):
            return apology("most provide password", 400)

        # Ensure password and confirmation coincide
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        # Keep user logged
        session_as_sql_list = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = session_as_sql_list[0]["id"]

        # Return user to homepage
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Input variables
        symbol = request.form.get("symbol")
        selling_shares = request.form.get("shares")
        quote = lookup(symbol)

        # Ensure symbol is in database
        if not quote:
            return apology("invalid symbol", 400)

        # Ensure user set selling shares
        if not selling_shares:
            return apology("invalid amount of shares")

        # Calculate selling price
        selling_price = quote["price"] * float(selling_shares)

        # User's balance before sale
        b_balance_list = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        b_balance = b_balance_list[0]["cash"]

        # User's balance after sale
        a_balance = b_balance + selling_price

        # Ensure user has enough shares to sell
        wallet_info = db.execute("SELECT shares FROM wallets WHERE person_id = ? AND symbol = ?", session["user_id"], symbol)
        owned_shares = float(wallet_info[0]["shares"])
        if owned_shares < float(selling_shares):
            return apology("purchase declined - insufficient shares", 400)

        # User's shares after sale
        owned_shares = owned_shares - float(selling_shares)

        # Update user's balance after purchase
        new_balance = db.execute("UPDATE users SET cash = ? WHERE id = ?", a_balance, session["user_id"])

        # Add purchase to purchases database
        new_sell = db.execute("INSERT INTO purchases (person_id, symbol, price, shares, transaction_type) VALUES (?, ?, ?, ?, ?)",
                              session["user_id"], symbol, quote["price"], selling_shares, "SELL")

        # Add purchase to wallet
        symbol_in_wallet = db.execute("SELECT shares FROM wallets WHERE person_id = ? AND symbol = ?", session["user_id"], symbol)
        if not symbol_in_wallet:
            addto_wallet = db.execute("INSERT INTO wallets (person_id, shares, symbol) VALUES (?, ?, ?)",
                                      session["user_id"], owned_shares, symbol)
        else:
            addto_wallet = db.execute("UPDATE wallets SET shares = ? WHERE person_id = ? AND symbol = ?",
                                      owned_shares, session["user_id"], symbol)

        # Erase symbol from wallet if user sells all their shares
        if owned_shares == 0 or owned_shares == None:
            erasefrom_wallet = db.execute("DELETE FROM wallets WHERE person_id = ? AND symbol = ?", session["user_id"], symbol)

        return redirect("/")

    # If user gets to page via GET
    else:

        # List of symbols of companies with owned shares
        owned_companies = db.execute("SELECT symbol FROM wallets WHERE person_id=? GROUP BY symbol", session["user_id"])

        # Return template
        return render_template("sell.html", owned_companies=owned_companies)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash to user's wallet"""
    if request.method == "POST":
        added_cash = float(request.form.get("cash"))
        # User's current cash as a SQL list of dicts
        current_cash_list = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        current_cash = current_cash_list[0]["cash"]

        # New amount of user's cash
        new_cash = current_cash + added_cash

        # Update user's cash in database
        update_cash = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

        return redirect("/")

    else:
        return render_template("add_cash.html")

