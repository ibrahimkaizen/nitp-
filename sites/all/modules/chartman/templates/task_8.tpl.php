<!-- TAble 1 -->
<div>
    <h2 class="pane-title">10 Days Overview - Test Type</h2>
    <table>
        <thead>
            <tr>
                <th>DATE SPECIMEN TESTED</th>
                <th>INITIAL</th>
                <th>REPEAT</th>
                <th>FOLLOW UP</th>
                <th>MISSING</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($table_1 as $item): ?>
                <tr>
                    <td><?php print $item['label']; ?></td>
                    <td><?php print $item['initial']; ?></td>
                    <td><?php print $item['repeat']; ?></td>
                    <td><?php print $item['followup']; ?></td>
                    <td><?php print $item['missing']; ?></td>
                    <td><?php print $item['total']; ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
        <tfoot>

        </tfoot>
    </table>

</div>

<!-- TAble 2 -->

<div>
    <h2 class="pane-title">10 Days Overview - Positive</h2>
    <table>
        <thead>
            <tr>
                <th>DATE SPECIMEN TESTED</th>
                <th>INITIAL</th>
                <th>REPEAT</th>
                <th>FOLLOW UP</th>
                <th>MISSING</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($table_2 as $item): ?>
                <tr>
                    <td><?php print $item['label']; ?></td>
                    <td><?php print $item['initial']; ?></td>
                    <td><?php print $item['repeat']; ?></td>
                    <td><?php print $item['followup']; ?></td>
                    <td><?php print $item['missing']; ?></td>
                    <td><?php print $item['total']; ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
        <tfoot>

        </tfoot>
    </table>

</div>

<!-- Third Table -->

<div>
    <h2 class="pane-title">10 Days Overview - Public/Private Lab</h2>
    <table>
        <thead>
            <tr>
                <th>DATE SPECIMEN TESTED</th>
                <th>PUBLIC</th>
                <th>PRIVATE</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($table_3 as $item): ?>
                <tr>
                    <td><?php print $item['label']; ?></td>
                    <td><?php print $item['public']; ?></td>
                    <td><?php print $item['private']; ?></td>
                    <td><?php print $item['total']; ?></td>
                </tr>
            <?php endforeach; ?>
        </tbody>
        <tfoot>

        </tfoot>
    </table>

</div>
