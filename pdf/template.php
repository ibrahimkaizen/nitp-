<!DOCTYPE html>
<html>
<head>
    <title></title>
    <style>
        .content {
            margin-top: 15em;
        }
        table {
            width: 100%;
            vertical-align: bottom;
        }
        .center {
            text-align: center;
        }
    </style>
</head>

<body style="background-image: url(<?php print $base64; ?>); background-repeat: no-repeat;background-size: cover;">
    <div class="content">
        <table class="center">
            <tbody>
                <tr>
                    <td>
                        <img src="<?php print $dataUri; ?>">
                    </td>
                    <td>
                        <h2>
                            <?php print $username[0]; ?> <br>
                            <?php print $username[1]; ?> <br>
                            <?php if (isset($username[2])):?><?php print $username[2]; ?><?php endif; ?>
                        </h2>
                        <h2><?php print $node['passport']; ?></h2>
                    </td>
                </tr>
            </tbody>
        </table>

        <table class="center">
            <tbody>
                <tr>
                    <td>
                        <h2>
                            <?php print $node['specimenid']; ?><br>
                            <?php print $node['shortresult']; ?>
                        </h2>

                        <h3>
                            Tested on: <br>
                            <?php print $node['testdate']; ?>
                        </h3>
                    </td>
                </tr>
            </tbody>
        </table>

        <h4 style="padding-left:80px;">Authorized Test Center: <?php print $node['lab']; ?></h4>

    </div>



</body>

</html>
