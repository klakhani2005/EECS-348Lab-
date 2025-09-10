<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PHP Multiplication Table</title>
    <style>
        table {
            border-collapse: collapse;
            margin-top: 20px;
        }
        th, td {
            border: 1px solid black;
            padding: 8px;
            text-align: center;
        }
        th {
            background-color: #f2f2f2;
        }
        input[type=number] {
            width: 50px;
        }
    </style>
</head>
<body>
    <h1>PHP Multiplication Table</h1>

    <form method="post">
        Enter a number: 
        <input type="number" name="number" min="1" required>
        <input type="submit" value="Generate Table">
    </form>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $num = intval($_POST["number"]);

        echo "<h2>Multiplication Table up to $num</h2>";
        echo "<table>";

        // Table header row
        echo "<tr><th></th>"; // empty top-left cell
        for ($col = 1; $col <= $num; $col++) {
            echo "<th>Col $col</th>";
        }
        echo "</tr>";

        // Table rows
        for ($row = 1; $row <= $num; $row++) {
            echo "<tr>";
            echo "<th>Row $row</th>"; // row header
            for ($col = 1; $col <= $num; $col++) {
                echo "<td>" . ($row * $col) . "</td>";
            }
            echo "</tr>";
        }

        echo "</table>";
    }
    ?>
</body>
</html>
