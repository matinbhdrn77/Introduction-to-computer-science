-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT street, description FROM crime_scene_reports WHERE year = "2020" AND month = "7" AND day ="28";
-- Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
--Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
SELECT name,transcript FROM interviews WHERE year = "2020" AND month = "7" AND day ="28" AND transcript LIKE "%courthouse%";
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If
--you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time
--frame.

--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at
--the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked
--the person on the other end of the phone to purchase the flight ticket.

SELECT minute,license_plate FROM courthouse_security_logs WHERE day = "28" AND hour = "10" AND activity = "exit";

minute | license_plate
16 | 5P2BI95
18 | 94KL13X
18 | 6P58WS2
19 | 4328GD8
20 | G412CB7
21 | L93JTIZ
23 | 322W7JE
23 | 0NTHK55

SELECT account_number, amount FROM atm_transactions WHERE month = "7" AND day = "28" AND atm_location LIKE "%Fifer Street%" AND transaction_type = "withdraw";

account_number | amount
28500762 | 48
28296815 | 20
76054385 | 60
49610011 | 50
16153065 | 80
25506511 | 20
81061156 | 30
26013199 | 35

SELECT caller, receiver,duration FROM phone_calls WHERE day = "28" AND duration < 61;

caller | receiver | duration
(130) 555-0289 | (996) 555-8899 | 51
(499) 555-9472 | (892) 555-8872 | 36
(367) 555-5533 | (375) 555-8161 | 45
(609) 555-5876 | (389) 555-5198 | 60
(499) 555-9472 | (717) 555-1342 | 50
(286) 555-6063 | (676) 555-6554 | 43
(770) 555-1861 | (725) 555-3243 | 49
(031) 555-6622 | (910) 555-3251 | 38
(826) 555-1652 | (066) 555-9701 | 55
(338) 555-6650 | (704) 555-2131 | 54

flights:
id | destination_airport_id | hour | minute
36| 4 | 8 | 20

SELECT * FROM airports WHERE id = "4";
4 | LHR | Heathrow Airport | London

SELECT passport_number, seat FROM passengers WHERE flight_id = "36";
7214083635 | 2A
1695452385 | 3B
5773159633 | 4A
1540955065 | 5C
8294398571 | 6C
1988161715 | 6D
9878712108 | 7A
8496433585 | 7B

SELECT name FROM people
   ...> WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = "28" AND duration < 60)
   ...> AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = "36")
   ...> AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND hour = "10" AND activity = "exit")
   
name
Roger
Madison
Evelyn
Ernest