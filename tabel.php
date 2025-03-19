<?php include_once "layout/header.php"; ?>
<?php include_once "layout/navbar.php"; ?>

<div class="container mt-5">
    <h2 class="text-center"><strong>Tabel</strong></h2>

    <table class="table mt-4 text-center table-striped table-bordered border-dark">
        <thead>
            <tr>
                <th scope="col">Nomor</th>
                <th scope="col">Status</th>
                <th scope="col">Status LED</th>
                <th scope="col">Waktu</th>
            </tr>
        </thead>
        <tbody class="table-group-divider">

        <?php 
        include_once "config/database.php";
        $query = "SELECT * FROM status_data ORDER BY id DESC LIMIT 20";
        $result = mysqli_query($conn, $query);

        while ($row = mysqli_fetch_array($result)){


        ?>
            <tr>
                <th scope="row"><?php echo $row ['id']; ?></th>
                <td><?php echo $row ['status']; ?></td>
                <td><?php echo $row ['status_led']; ?></td>
                <td><?php echo $row ['timestamp']; ?></td>
            </tr>
           
            <?php } ?>
        </tbody>
    </table>

    <br>
    <br>

</div>




<?php include_once "layout/footer.php"; ?>