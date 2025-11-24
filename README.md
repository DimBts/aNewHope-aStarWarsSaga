# aNewHope-aStarWarsSaga
Console Game

## Περιγραφή Παιχνιδιού

Το A New Hope είναι ένα παιχνίδι στρατηγικής σε γλώσσα C, εμπνευσμένο από το σύμπαν του Star Wars.
Ο παίκτης αναλαμβάνει τον ρόλο της Princess Leia, η οποία προσπαθεί να φτάσει στο R2-D2 μέσα σε ένα διαδραστικό πίνακα, αποφεύγοντας:

Τον Darth Vader

Τους περιπολούντες Stormtroopers

Τα εμπόδια (X)

Ο πίνακας αλλάζει σε κάθε παιχνίδι, οι εχθροί κινούνται δυναμικά και η δυσκολία επηρεάζει τόσο τον αριθμό όσο και τη συμπεριφορά τους.

## Gameplay

Ο παίκτης βλέπει μόνο τη γραμμή και τη στήλη όπου βρίσκεται η Leia (τα υπόλοιπα είναι κρυμμένα).

Τα Stormtroopers κινούνται σε προκαθορισμένη κατεύθυνση και αναπηδούν όταν συναντήσουν εμπόδια.

Ο Darth Vader πλησιάζει τη Leia κάθε 2 κινήσεις.

Αν η Leia φτάσει τον R2-D2 → Νίκη

Αν τη φτάσει ο Vader ή μείνει από ζωές → Ήττα

## Χειρισμός

Ο παίκτης δίνει ακολουθία κινήσεων:

Πλήκτρο	Κίνηση
U	Πάνω
D	Κάτω
L	Αριστερά
R	Δεξιά
X	Έξοδος παιχνιδιού

Μπορούν να δοθούν πολλαπλές κινήσεις μαζί (π.χ. UURDL).
Η είσοδος από το πληκτρλόγιο ειναι case insensitive.

## Επιλογές Δυσκολίας

Easy

Medium

Hard

Impossible (χωρίς εμπόδια, περισσότεροι stormtroopers)

Η δυσκολία αλλάζει το ποσοστό:

Εμποδίων

Stormtroopers

Ταχύτητα κινήσεων Vader
## Αντικείμενα Παιχνιδιού
Σύμβολο	Περιγραφή
L	Leia
R	R2-D2
D	Darth Vader
@	Stormtrooper
X	Εμπόδιο
#	Άγνωστο / κρυφό
.	Πεδίο ορατότητας Leia

## Οδηγίες Μεταγλώττισης & Εκτέλεσης
Linux / MacOS
gcc main.c -o anewhope
./anewhope

Windows (MinGW)
gcc main.c -o anewhope.exe
anewhope.exe

## Δομή Κώδικα

ModeValid() – Έλεγχος και επιλογή δυσκολίας

TableInVal() – Έλεγχος εισόδου για διαστάσεις πίνακα

Board() – Δέσμευση μνήμης & αρχικοποίηση πίνακα

ModeSelect() – Δημιουργία εμποδίων, υπολογισμός stormtroopers

InitialChar() – Τοποθέτηση όλων των χαρακτήρων στον πίνακα

getLeiaMoves() – Λήψη κινήσεων χρήστη

LeiaMoves() – Επεξεργασία κινήσεων

VaderMoves() – Αλγόριθμος δίωξης

TroopGen() / Patrol() – Δημιουργία και κίνηση stormtroopers

CheckWinLose() – Έλεγχος κατάστασης παιχνιδιού

## Παραδείγματα Εξόδου

![1](/images/newHope_menu.png)

![2](/images/newHope_starting_board.png)

![3](/images/newHope_moveNpatrol.png)

![4](/images/newHope_trooperhit.png)

![5](/images/newHope_vaderChase.png)

![5](/images/newHope_gameLost.png)
