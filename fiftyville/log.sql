-- First, I'll check the description on the crime scene reports table to get a sense of what happened:
-- SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

-- Now, since every witness mentioned the bakery, I'll check their security logs to see if there's anything useful there. BTW,
-- they mentioned on the description that "littering took place at 16:36" and that there were no witnesses. I don't know yet why that's relevant,
-- but I'll keep it in mind.

-- I'll check what "activities" occured at the time of the theft
-- SELECT activity FROM bakery_security_logs WHERE month = 7 AND day = 28;
-- That ony shows entrances and exits, presumably from workers or clients. I don't find that useful right now.

-- Let's check the interviews
-- SELECT transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- Nice information from the interviews:
-- The thief got out of the bakery's parking lot at aproximately 10:25 so I can check the license plate of their car
-- The thief withdraw money from the ATM before entering the bakery (don't know if this is useful)
-- The thief said he was going out of Fiftyville on the earliest flight the day after the theft, so I can check where did he go

-- I checked the schema of the people table and it seems that I can get the name of the person by its license plate. Let find the plate
-- SELECT license_plate
--     FROM bakery_security_logs
--         WHERE month = 7
--         AND day = 28
--         AND hour = 10
--         AND minute > 15 AND minute < 30
--         AND activity = "exit";

-- While running that query, I found the plates of my eight first suspects. With that info, I can find their names and then check
-- if they took a flight the day after the theft.

-- I found the names of the eight suspects with:
-- SELECT name FROM people
--     WHERE license_plate IN (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE month = 7
--     AND day = 28
--     AND hour = 10
--     AND minute > 15 AND minute > 30
--     AND activity = "exit");

-- Let's see what flights were available the next day and the earlier one:
-- By checking the flights table, I found that the destination airport id is "4" with:
-- SELECT destination_airport_id, hour
--     FROM flights
--     WHERE month = 7
--     AND day = 29
--     ORDER BY hour;

-- Now let's see, on the table 'airports', which was the thief's destination;
-- SELECT city FROM airports WHERE id = 4;

-- It seems that the thief went to New York City. That's the answer of question #2.
-- Let's get the ID of that flight:
-- SELECT id FROM flights
--     WHERE destination_airport_id = 4
--     AND month = 7
--     AND day = 29;
-- The resulting flight ID is '36'


-- Now let's find out, joining the 'people' and 'passenger' tables, who on that flight had a license plate that
-- coincides with those of the bakery security logs. As a result, I'll get the passport number:

-- That was faulty. I first need to find the passport numbers from the people who exited the bakery's parking lot, using
-- their license plate, and then look for matches with the flight's passengers:
-- SELECT passport_number
--     FROM people
--     WHERE license_plate IN (
--     SELECT license_plate
--     FROM bakery_security_logs
--     WHERE month = 7
--     AND day = 28
--     AND hour = 10
--     AND minute > 15 AND minute > 30);

-- Now that I got the passports, let's join everything in one big query:
-- SELECT passport_number
--     FROM passengers
--     WHERE flight_id = 36
--     AND passport_number IN (
--         SELECT passport_number
    --     FROM people
    --     WHERE license_plate IN (
        --     SELECT license_plate
        --     FROM bakery_security_logs
        --     WHERE month = 7
        --     AND day = 28
        --     AND hour = 10
        --     AND minute > 15 AND minute > 30));

-- Now the list of suspects is down to 4, who's passports I got and who's names I'm gonna find out with:--

-- Well, before doing this, I found that the queries were getting to complex for no reason since I was recommended to keep a list
-- of suspects. So, since I can do that, I went back to the query that gave me the names of my first eight suspects and their names are:
-- Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey and Bruce.

-- Now let's repeat the last query that gave me four passport numbers but let's select the one that matches any of those names:

-- SELECT name FROM people WHERE passport_number IN (
    -- SELECT passport_number
        -- FROM passengers
        -- WHHERE flight_id = 36
        -- AND passport_number IN (
            -- SELECT passport_number
                -- FROM people
                -- WHERE name = "Vanessa" OR name = "Barry" OR name = "Iman" OR name = "Sofia" OR name = "Luca" OR name = "Diana" OR name = "Bruce"));

-- With that, I reduced the list to just three names: Sofia, Luca and Bruce.
-- I went on to find who used the ATM the day of the thief using:
-- SELECT name
    -- FROM people
    -- WHERE id IN (
        -- SELECT person_id
        -- FROM bank_accounts
        -- WHERE account_number IN (
            -- SELECT account_number
            -- FROM atm_transactions
            -- WHERE month = 7
            -- AND day = 28
            -- AND atm_location = "Humphrey Street")
        -- AND name = "Sofia" OR name = "Luca" OR name = "Bruce");

-- And even tho I hoped this was going to be the final query before knowing the name of the thief, it only reduced the list to
-- two suspects: Luca and Bruce.

-- With those names, I found the phone number of the only person who did a call the day of the theft and whose name was
-- either "Luca" or "Bruce". The phone name is (367) 555-5533 and I found it with:

-- SELECT caller
    -- FROM phone_calls
    -- WHERE caller IN (
        -- SELECT phone_number
            -- FROM people
            -- WHERE name = "Luca" OR name = "Bruce")
    -- AND month = 7
    -- AND day = 28;

-- Now, let's find the name with:

-- SELECT name
-- FROM people
-- WHERE phone_number = "(367) 555-5533";

-- AND NOW... *redoble de tambores*
-- FINALLY...
-- WE KNOW...
-- THAT THE THIEF...
-- IS...
-- ...
-- ...
-- Bruce!!!

-- Great. Now let's quickly find the name of the person who helped him with:

-- SELECT name
    -- FROM people
    -- WHERE phone_number = (
        -- SELECT receiver
        -- FROM phone_calls
        -- WHERE caller = "(367) 555-5533");

-- And the helper was: Pamela.

-- Mystery solved. This was _very_ fun... But wait! I made a mistake.

-- The accomplice wasn't Pamela, and it seems that the mistake was coming from a wrong checking on the phone_calls table.
-- I solved it by adding the month and day of the call:

-- SELECT name
    -- FROM people
    -- WHERE phone_numer = (
        -- SELECT receiver
        -- FROM phone_calls
        -- WHERE caller = "(367) 555-5533"
        -- AND month = 7
        -- AND day = 28);

-- Now, I can see that the accomplice was actually Robin. Now, oficially: mystery solved.

