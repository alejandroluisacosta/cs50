from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Sessions use filesystem instead of signed cookies
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure database
db = SQL("sqlite:///project.db")


# Index page: Course's banner & Contact form
@app.route('/')
@login_required
def index():

    if request.method == 'GET':
        return render_template('index.html')

# Login
@app.route("/login", methods=["GET", "POST"])
def login():

    # Clear all existing sessions
    session.clear()

    # User fills login form
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("introduce un nombre de usuario", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("introduce una contraseña", 403)

        # Query database for username
        users = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(users) != 1 or not check_password_hash(users[0]["hash"], request.form.get("password")):
            return apology("nombre de usuario/contraseña incorrecta", 403)

        # Remember which user has logged in
        session["user_id"] = users[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reaches page through GET
    else:
        return render_template("login.html")

# Logout
@app.route('/logout')
def logout():

    # Clear all sessions
    session.clear()

    # Redirect to login form
    return redirect('/')


# Register a new user
@app.route('/register', methods=['GET', 'POST'])
def register():

    # Data variables
    username = request.form.get("username")
    password = request.form.get("password")
    existing_usernames_db = db.execute("SELECT username FROM users")
    existing_usernames_list = [d['username'] for d in existing_usernames_db] # Transform list of dicts into list

    # If user fills form
    if request.method == "POST":
        # Ensure username was submited
        if not request.form.get("username"):
            return apology("introduce un nombre de usuario", 400)

        # Ensure username is available
        elif request.form.get("username") in existing_usernames_list:
            return apology("nombre de usuario no disponible", 400)

        # Ensure password was submited
        elif not request.form.get("password"):
            return apology("introduce una contraseña", 400)

        # Ensure password and confirmation coincide
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("las contraseñas no coinciden", 400)

        new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))

        # Keep user logged
        session_as_sql_list = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = session_as_sql_list[0]["id"]

        # Return user to homepage
        return redirect("/")

    # User reached route via GET
    else:
        return render_template("register.html")


# Course's lessons
@app.route('/lessons')
@login_required
def lessons():

    # Render lessons template
    return render_template("lessons.html")


# Change password
@app.route('/change_password', methods=['GET', 'POST'])
@login_required
def change_password():

    # Data variables
    password = request.form.get("password")
    new_password = request.form.get("new_password")
    confirmation = request.form.get("confirmation")
    user_info_db = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    # User fills form
    if request.method == 'POST':

        # Return apology if passwords don't match
        if new_password != confirmation:
            return apology("Las contraseñas no coinciden", 400)

        # Update user's password in database
        change_password = db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(new_password), session["user_id"])

        return redirect("/password_changed")

    # User gets to page through GET request
    if request.method == 'GET':
        return render_template("/change_password.html")
