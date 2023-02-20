-- write settings and queries here and run
-- sqlite3 inf2700_orders.sqlite3 < assi.quit^C^Cueries.sql
-- to perform the queries

-- -- TASK 2, a)
-- .mode column
-- .header on
-- SELECT customerName, contactLastName, contactFirstName
-- FROM Customers



-- -- TASK 2, b)
-- .mode column
-- .header on
-- SELECT *
-- FROM Orders
-- WHERE shippedDate IS NULL


-- -- TASK 2, c)
-- .mode column
-- .header on
-- SELECT C.customerName AS Customers, SUM(OD.quantityOrdered) AS Total
-- FROM Orders O, Customers C, OrderDetails OD 
-- WHERE O.customerNumber = C.customerNumber AND O.orderNumber = OD.orderNumber
-- Group by O.customerNumber
-- ORDER BY Total DESC



-- -- TASK 2, d)
-- .mode column
-- .header on
-- SELECT P.productName, T.totalQuantityOrdered
-- FROM Products P NATURAL JOIN (SELECT productCode, SUM(quantityOrdered) AS totalQuantityOrdered
-- FROM OrderDetails
-- GROUP BY productCode) AS T
-- WHERE T.totalQuantityOrdered >= 1000;


-- -- TASK 3, 1)
-- .mode column
-- .header on
-- SELECT C.country, C.customerName FROM Customers C
-- WHERE country LIKE '%Norway%' 

-- TASK 3, 2) 
-- Retrieve all classic car products and their scale.
-- .mode column
-- .header on
-- SELECT P.productName AS ProductName, P.productScale AS Scale, P.productLine 
-- FROM Products P
-- WHERE P.productLine == 'Classic Cars'
-- ORDER BY P.productScale


-- TASK 3, 3) 
-- Create a list of incomplete orders (order status is "In process").
-- The list must contain order-Number, requiredDate, productName, quantityOrdered and quantityInStock.
-- .mode column
-- .header on
-- SELECT O.orderNumber, O.status, O.requiredDate, P.productName, OD.quantityOrdered, P.quantityInStock
-- FROM Orders O, Products P, OrderDetails OD
-- WHERE O.orderNumber = OD.orderNumber AND P.productCode = OD.productCode AND O.status = 'In Process'




-- --Task 3, 4)
-- --Create a list of customers.  where the difference between the 
-- --total price of all ordered products and the total amount of all payments exceeds the credit limit.
-- --The list must contain the customer name, credit limit, total price, total payment and the difference between the two sums.
-- .mode column
-- .header on
-- SELECT C.customerName, C.creditLimit, P.amount AS TotalOrder, P.amount - C.creditLimit AS Difference
-- FROM Customers C, payments P
-- WHERE P.amount > C.creditLimit
-- GROUP BY C.customerName


--Task 3, 5)
--Create a list of customers who have ordered all the products that customer 219 has ordered.
.mode column
.header on
WITH Products219(productCode) AS (
    SELECT productCode
    FROM Orders NATURAL JOIN OrderDetails
    WHERE customerNumber = 219
)

SELECT customerNumber, customerName
FROM Orders NATURAL JOIN OrderDetails NATURAL JOIN Customers
WHERE productCode IN products219 AND customerNumber != 219
GROUP BY customerNumber
Having COUNT(DISTINCT productCode) = (SELECT COUNT(*) FROM Products219)
ORDER BY customerNumber