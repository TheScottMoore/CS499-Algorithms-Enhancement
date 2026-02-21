# CS499-Algorithms-Enhancement
Enhancement for Algorithm/Data Structure category for CS Capstone

This artifact was originally developed for CS-340: Client/Server Development. The application was written in Python and connected to a MongoDB database to manage records for trained rescue animals sourced from animal shelters. The original purpose of this project within CS-340 was to demonstrate the ability to link the front-end and back-end components into a working web application.

The indexing strategy reduces the average complexity for queries to O(1) from O(n), which is a very significant improvement, especially as the application were to scale.

The sorted vector and binary search combination reduces the complexity from O(n). The vector sorting algorithm executes at O(n log n) and afte the binary search range is implemented, the total average complexity ends at O(log n + k), where k is the number of results returned.

Shifting computational cost using data structures from the C++ Standard Template Library greatly improves performance and ultimately scalability.

Hash-based indexing
<img width="793" height="56" alt="6fef396e-2faa-482b-8f7a-a2816d734b21" src="https://github.com/user-attachments/assets/482cb338-7096-42bb-9f9e-8e2042f8c690" />
<img width="782" height="95" alt="15a982a8-173b-4d31-8921-64406acf6bb7" src="https://github.com/user-attachments/assets/b019a7ad-3594-4446-ba1a-1dd6731d4cd9" />

Binary Search after vector sort
<img width="789" height="380" alt="56e58eb7-1097-4c2c-a78a-2200bbb74518" src="https://github.com/user-attachments/assets/38bad039-4d95-4513-8fd2-1f0f99b8903b" />
<img width="780" height="115" alt="686d016a-4c62-4666-ae01-3763089d4894" src="https://github.com/user-attachments/assets/fdb142eb-4d40-4138-9ddc-0011c2ecbb80" />


