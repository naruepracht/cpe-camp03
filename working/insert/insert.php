<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>TEST INSERT DATA</title>
</head>
<body>
<?php
// ประกาศตัวแปล $conn เชื่อมต่อกับระบบฐานข้อมูล
$conn = new mysqli("localhost", "toon", "", "naruepracht");
mysqli_set_charset($conn,"utf8");
// ถ้า การเชื่อมต่อกับฐานข้อมูล มีข้อผิดพลาด
if ($conn->connect_error) {
// แสดงข้อผิดพลาด
die("เชื่อมต่อล้มเหลว: รายละเอียดข้อผิดพลาด " . $conn->connect_error);
}
// ประกาศตัวแปล $sql เก็บโค้ด SQL ไว้
$sql = "INSERT INTO studentcode (Name, Code) VALUES ('Jujuju', '6040202589')";
// ถ้า โค้ด SQL รันผ่าน
if ($conn->query($sql) === TRUE) {
// แสดงข้อความ สำเร็จ
echo "เพิ่มข้อมูลเรียบร้อยแล้ว!";
} else { // ถ้า โค้ด SQL รันไม่ผา่น
// แสดงข้อความ ล้มเหลว
echo "ผิดพลาด: " . $sql . "<br>" . $conn->error;
}
// ปิดการเชื่อมต่อกับฐานข้อมูล
$conn->close();
?>
</body>
</html>