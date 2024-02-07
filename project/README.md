# Detox Mental

#### Video Demo: https://youtu.be/twUfROajpBY
#### Description:

"Detox Mental" is a web application that hosts an audiocurse with the same name. It was developed using HTML, CSS, JavaScript, SQL, Python and Flask.

To give some context: Detox Mental (the couse, not the web app) is an audiocourse created completely in Spanish. It's based on lessons and exercises designed for people who have a very active mind, a mind that's constantly worrying, procrastinating, and giving up to fears, all of which stops them from undertaking the goals and projects they so badly wish to accomplish. Originally, the course was merely a blog post, but given its popularity, the course was born.

This web app consists on five main features: an Index page ("Inicio"), a lessons page ("Curso"), a registration and a login page ("Registro" and "Iniciar cesión", respectively), a page for password changing ("Cambiar contraseña"), and a logout route ("Cerrar sesión").

## Inicio (Index)

The index page is simple yet useful enough to be a part of the project. At the moment, it consists on a big banner that gives a reminder to students of three main rules for taking the course: to always have pen and paper at hand, to listen carefully but discard that which doesn't make sense for them, and to be honest with themselves while taking the lessons, since the ideas that are gonna come out aren't necessarily going to be pretty to observe.

Down below the banner there's a button that takes the user to the course's lessons. The original idea was to have an email form which, taking advantage of the Flask-Mail library, could serve as a feedback tool for me to see if there's any kind of problem (or questions) related to the course or website. The reason it wasn't included is that the inclution of the Flask-Mail library was rising a strange error I couldn't solve, and since this is a first version of the platform, the decision was to keep it simple for the moment and keep researching the problem with the hopes of adding the form soon.

## Curso (Lessons)

Being the main part of the project, *Curso* hosts all the lessons and exercises of the course in one place.

The structure of the audiocourse is as follows: it's a 30-day-course which consists on an audio session followed by an exercise, followed by another session and it's respective exercise...

So on day one you'll be listening to session #1. On day two, you'll do exercise #1. On day three you'll listen to session #2, and so on until you reach lesson #15 and exercise #15 (for practical purposes, this web app only hosts the fisrt half of the course at the moment).

On *Curso*, the first element on the top is a decorative banner with the name of the course, and below that there are two buttons: one for each available part of the course.

The buttons were taken from Bootstrap and their background color was changed by a CSS file called "style.css." The intention was to also change the default color they acquire when clicked on, but it'll remain as another change to make in the near future.

When you click on the "Parte 1" button, you'll see the first three sets of lessons-exercises deployed. If you click on the other one, you'll see the second three sets (meaning lesson/exercise #4, #5 and #6.)

The lessons are represented by smaller banners with links to YouTube videos where the audios are available to listen. They're listed as private so only users of the course can access them.

In between those smaller banners are other buttons, each one representing an exercise. In this case, clicking a button will automatically render a text in the screen, which, as expected, has the instructions for doing the exercise for the day. One thing to improve in this respect is the fact that the texts are simply written in the `lessons.html` template instead of a separate `.txt` file for each of the exercises. Another imrpovement to add in the future.

The challenge with the buttons was to make them be in-page responsive instead of redirecting users to other pages only to see the text, and to make this possible, two JavaScrip scripts were needed.

The first one adds *onclick* events to the "part" buttons so they display the required lessons and exercises. The second script adds events to the "exercise" buttons so they display the requested exercise and hides all other exercise texts. This last feature intends a better user experience with a less cluttered page.

One future improvement for the *Curso* page is to make the "part" buttons not only display what's requested, but to hide everything else.

At the moment, if you click on *Parte 1* and immediately click *Parte 2* afterwards, both parts are going to be displayed on the page. There were several attempts to include this feat, but since they didn't work and the interface doesn't seem extremely cluttered with both parts displayed, it "made the cut" for the time being.

## Iniciar sesión (Login), Registro (Register), Cambiar contraseña (Change password) and Cerrar sesión (Logout)

There's not that much to comment about this features. They do as expected: register a new user, log them in, change their password if they want to, and log them out.

They also handle user errors like forgetting to input a username, password, try to change their password but the confirmation isn't right...

If any of this happens, user's will be redirected to an apology page with a picture of a suspicious-looking dog and a description of the problem.

All of this is accomplished via Python functions, all written in the `app.py` document found in the project directory.

## Conclusions

Detox Mental is a simple and user-friendly web app, and it was born with the intention of being improved over time with more and more interesting features.

The Detox Mental course was already made before I started CS50x, and when I saw that there was a final project and that it could be something like a web page, the decision was clear to take.

The more obvious improvements for this 1.0 web app are:

- Adding a problem report/questions form to the *Inicio* page.
- Uploading the remaining of the course (parts #3, #4 and #5).
- Changing the color of the buttons after they are clicked on.
- Taking the exercises' texts out of the `lessons.html` template into separate text files. One for each exercise.
- Changing the script used for the "part" buttons so, when you click on one of them, its content is displayed and the others' are hidden.

This was my project. I learned *a lot* by creating a complete web app by my own and had much fun doing it.

Thank y'all in the CS50 staff. This was great.