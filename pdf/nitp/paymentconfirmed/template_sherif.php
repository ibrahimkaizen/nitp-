<!DOCTYPE html>
<html>
<head>
    <title></title>
    <style>
        body {
            font-size: 12px;
        }
        table {
            width: 100%;
            vertical-align: bottom;
        }
        .center {
            text-align: center;
        }
        .placement {
            position: absolute;
            left: 3.7em;
        }
        .float {
            float:left;
        }
        .left {
            width: 175px;
        }
    </style>
</head>

<body style="background-image: url(<?php print $base64; ?>); background-repeat: no-repeat;background-size: cover;">
    
    <div class="placement" style="top: 8em;">
        <div style="float:right;"><img src="<?php print $dataUri; ?>"></div>
    </div>
    
    <div class="placement" style="top: 16.1em;">
        <div class="float left"><?php print $response["phone"]; ?></div>
        <div class="float"><?php print $response["flight_no"]; ?></div>
    </div>
    
    <div class="placement" style="top: 19.2em;">
        <div class="float left"><?php print $response["sex"]; ?></div>
        <div class="float"><?php print $response["nationality"]; ?></div>
    </div>
    
    <div class="placement" style="top: 22.6em;">
        <div class="float left"><?php print $response["dob"]; ?></div>
        <div class="float"><?php print $response["country"]; ?></div>
    </div>
   
    <div class="placement" style="top: 28em;">
        <div class="float left"><?php print $response["flight_no"]; ?></div>
        <div class="float" style="width: 220px;"><?php print $response["departure_airport"]; ?></div>
        <div class="float"><?php print $response["arrival_location"]; ?></div>
    </div>
    
    <div class="placement" style="top: 35.5em;left:6.5em;">
        <div class="float"><?php print $response["visited"]; ?></div>
    </div>
    
    
    <div class="placement" style="top: 42em;">
        <div class="float" style="width: 137px;"><?php print $response["destination_address"]; ?></div>
        <div class="float" style="width: 220px;"><?php print $response["destination_city"]; ?></div>
        <div class="float"><?php print $response["destination_phone"]; ?></div>
    </div>
    
    
    <div class="placement" style="top: 49.3em;">
        <div class="float" style="width: 180px;"><?php print $response["emergency_name"]; ?></div>
        <div class="float" style="width: 220px;"><?php print $response["emergency_phone"]; ?></div>
        <div class="float"><?php print $response["emergency_address"]; ?></div>
    </div>
    
     <div class="placement" style="top: 57.5em;">
        <div class="float" style="width: 180px;font-size:10px;"><?php print $response["symptoms"]; ?></div>
        <div class="float" style="width: 250px;font-size:10px;"><?php print $response["sick"]; ?></div>
        <div class="float" style="font-size:10px;"><?php print $response["medications"]; ?></div>
    </div>
    
    
    
    
     <div class="placement" style="left: 7em; top: 67em;">
        <div class="float" style="width: 180px;"><?php print $response["fullname"]; ?></div>
        <div class="float" style="width: 250px;"></div>
        <div class="float"><?php print $response["post_date"]; ?></div>
    </div>
    
    
</body>

</html>
