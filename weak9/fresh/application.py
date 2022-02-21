from cs50 import SQL
from flask import Flask, redirect, render_template, request

app = Flask(__name__)

SPORTS = [
    'football',
    'vollyball', 
    'box',
    'running'
]

db = SQL("sqlite:///froshims.db")

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    
    name = request.form.get("name")
    if not name:
        return render_template("fail.html", mess="you dont insert your name")
        
    sport = request.form.get("sport")
    if not sport:
        return render_template("fail.html", mess="you dont insert your sport")
        
    if sport not in SPORTS:
        return render_template("fail.html", mess="innvalid sport")

    db.execute("INSERT INTO registrants (name, sport) VALUES (?, ?)", name, sport)        
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)