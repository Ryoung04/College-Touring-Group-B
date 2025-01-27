# College-Touring-Group-B
This C++ program is designed to assist college students in planning their college tours efficiently while keeping track of souvenirs and expenses. The application showcases an easy to follow interface, robust data handling, and functionality for both students and administrators.

Team Name: Team No Sleep
Product Owner: Reise Young
Scrum Master: Linsey Pram
Group Members: Octavio Albuquerque, Linsey Pram, Reise Young, Ruben Gonzalez, Extra Person

(Sprint 1) - Baseline Story
1. Display College Campuses and Distances
a) Description:
As a student, I can view a list of college campuses and their distances from Saddleback College so I can identify the starting point and distances to plan my trip.
b) Tasks:
As a student, I can view the list of all college campuses.
As a student, I can view the distances from Saddleback College to other campuses.
c) Tests:
Verify that the list of all campuses is displayed.
Verify that the distances between Saddleback College and each campus are displayed correctly.
Verify that invalid or missing input files are handled gracefully.
d) Assignee:
Reise: Responsible for implementing the data structure and displaying campus details.
e) Estimation:
8
f) Priority:
10
g) Done:
As a student, I can view the list of all campuses and their distances from Saddleback College, displayed in a readable format.

2. Display Souvenirs and Prices for a Campus
a) Description:
As a student, I can view the souvenirs and their prices for a specific campus so I can decide what to purchase when planning my trip.
b) Tasks:
As a student, I can select a campus from the list.
As a student, I can view the souvenirs and their prices for the selected campus.
c) Tests:
Verify that a student can select a campus to view souvenirs.
Verify that souvenirs and prices are displayed accurately for the selected campus.
Verify that invalid campus inputs are handled properly.
d) Assignee:
Reise: Implements the code to retrieve and display souvenir details.
e) Estimation:
7
f) Priority:
9
g) Done:
As a student, I can view souvenirs and prices for any selected campus from the list.

3. Plan Trip Starting at Saddleback College
a) Description:
As a student, I can plan a trip starting at Saddleback College to visit all campuses in the most efficient order.
b) Tasks:
As a student, I can calculate the most efficient route starting at Saddleback.
As a student, I can view the total distance traveled for the trip.
c) Tests:
Verify that the program calculates the shortest route to visit all campuses.
Verify that the total distance is displayed accurately.
d) Assignee:
Linsey: Implements the nearest-neighbor algorithm for trip planning.
e) Estimation:
9
f) Priority:
8
g) Done:
As a student, I can view the most efficient route starting at Saddleback College and the total distance traveled.

4. Add and Modify Souvenirs (Admin)
a) Description:
As an admin, I can add, update, and delete souvenirs and prices for each campus to ensure data remains accurate.
b) Tasks:
As an admin, I can log in using a secure password.
As an admin, I can add, update, or delete souvenirs and prices for campuses.
As an admin, I can save changes to ensure data persistence.
c) Tests:
Verify that an admin can successfully log in.
Verify that souvenirs can be added, updated, or deleted.
Verify that changes persist after restarting the program.
d) Assignee:
Linsey: Implements admin features and data persistence.
e) Estimation:
8
f) Priority:
10
g) Done:
As an admin, I can securely manage souvenirs and prices, with all changes persisting between sessions.

5. Design a User-Friendly Interface
a) Description:
As a user, I can navigate the program using a menu-driven interface for an intuitive experience.
b) Tasks:
As a user, I can view a main menu with all program options.
As a user, I can navigate through the menu options easily.
c) Tests:
Verify that the menu displays all program options.
Verify that all menu options are functional and accessible.
Verify input validation for invalid menu selections.
d) Assignee:
Ruben: Designs and implements the main menu interface.
e) Estimation:
8
f) Priority:
9
g) Done:
As a user, I can navigate through the program features using a simple and intuitive menu.

6. Plan Custom Trips
a) Description:
As a student, I can select specific campuses to visit and plan the most efficient route.
b) Tasks:
As a student, I can choose a starting campus.
As a student, I can select other campuses to visit.
As a student, I can calculate and view the shortest route for the selected campuses.
c) Tests:
Verify that a user can select a starting campus.
Verify that the shortest route is calculated for the selected campuses.
d) Assignee:
Ruben: Implements the route calculation for custom trips.
e) Estimation:
9
f) Priority:
8
g) Done:
As a student, I can select specific campuses, and the program calculates and displays the most efficient route.

7. Calculate Total Souvenir Costs During Trips
a) Description:
As a student, I can calculate the total cost of souvenirs purchased during a trip to track my expenses.
b) Tasks:
As a student, I can select souvenirs to purchase at each campus.
As a student, I can calculate and view the total costs per campus and for the entire trip.
c) Tests:
Verify the cost calculation for selected souvenirs at each campus.
Verify that the grand total for the trip is calculated accurately.
d) Assignee:
 Octavio: implements souvenir selection and cost calculations.
e) Estimation:
8
f) Priority:
9
g) Done:
As a student, I can select souvenirs during trips, and the program calculates and displays total expenses.

8. Plan Shortest Trip Starting at ASU
a) Description:
As a student, I can plan a trip starting at ASU to visit a specified number of campuses in the shortest possible distance.
b) Tasks:
As a student, I can input the number of campuses to visit.
As a student, I can calculate the shortest route starting at ASU.
As a student, I can view the route and total distance traveled.
c) Tests:
Verify the route for different input numbers of campuses.
Verify the total distance for each trip is accurate.
d) Assignee:
Octavio : Implements the trip planning algorithm for ASU.
e) Estimation:
10
f) Priority:
8
g) Done:
As a student, I can plan and view a trip starting at ASU, specifying the number of campuses to visit.

9. Add New Campuses (Admin)
a) Description:
As an admin, I can add new campuses and distances to the system to expand the data.
b) Tasks:
As an admin, I can read new campus data from an input file.
As an admin, I can add new campuses and distances to the system.
As an admin, I can validate the input file format.
c) Tests:
Verify new campuses are added correctly.
Verify invalid input files are handled gracefully.
d) Assignee:
New Person : Implements new campus addition functionality.
e) Estimation:
8
f) Priority:
7
g) Done:
As an admin, I can add new campuses from a validated input file.

10. Generate Trip Summary Report
a) Description:
As a student, I can view a summary report of my trip, including campuses visited, distances traveled, and souvenir costs.
b) Tasks:
As a student, I can compile all trip data into a summary.
As a student, I can view the summary report in a readable format.
c) Tests:
Verify the summary report includes all visited campuses.
Verify the total distance and costs in the report are accurate.
d) Assignee:
New Person : Implements trip summary reporting functionality.
e) Estimation:
8
f) Priority:
6
g) Done:
As a student, I can view a detailed and accurate summary report of my trip.
