<?php

require("../../dompdf/autoload.inc.php");
require("../../vendor/autoload.php");

use Dompdf\Dompdf;
use Endroid\QrCode\QrCode;

$dompdf = new Dompdf();

$options = $dompdf->getOptions();
$options->isRemoteEnabled(true);
$options->setIsHtml5ParserEnabled(true);
$dompdf->setOptions($options);

$nid = urlencode($_GET['nid']);
$url = 'https://projectdemo.com.ng/nitp/api/pdf/'. $nid . '/paymentcomfirmed.json';
$content = @file_get_contents($url);


if ($nid && $content == TRUE) {
    $response = json_decode($content, true);
    $path = 'bg.jpg';
    $data = file_get_contents($path);
    $type = pathinfo($path, PATHINFO_EXTENSION);
    $base64 = 'data:image/' . $type . ';base64,' . base64_encode($data);
    
    //Qr code
    $qrCode = new QrCode($response["qr_code"]);
    $qrCode->setSize(200);
    $dataUri = $qrCode->writeDataUri();
    
    
    ob_start();
    require('template.php');
    $html = ob_get_contents();
    ob_get_clean();
    
    $dompdf->loadHtml($html);
    $dompdf->render();
    
    // Output the generated PDF to Browser
    $dompdf->stream("Result.pdf", array("Attachment" => false));
    
    
} else {
    print "<!DOCTYPE html><html><body><h4>Slow network, please refresh.</h4></body></html>";
}

