<?php

require("dompdf/autoload.inc.php");
require("vendor/autoload.php");

use Dompdf\Dompdf;
use Endroid\QrCode\QrCode;

$dompdf = new Dompdf();

$options = $dompdf->getOptions();
$options->isRemoteEnabled(true);
$options->setIsHtml5ParserEnabled(true);
$dompdf->setOptions($options);

$id = urlencode($_GET['id']);
$id2 = urlencode($_GET['phone']);
$url = 'https://projectdemo.com.ng/nitp/api/app/'. $id . '/'. $id2;
$content = file_get_contents($url);
$response = json_decode($content, true);
$node = $response['nodes'][0]['node'];


if ( $node ) {
    $username = explode(' ', $node['username']);
    $path = 'bg.jpg';
    $data = file_get_contents($path);
    $type = pathinfo($path, PATHINFO_EXTENSION);
    $base64 = 'data:image/' . $type . ';base64,' . base64_encode($data);

    //Qr code
    $qrCode = new QrCode($node['qrlink']);
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
}


