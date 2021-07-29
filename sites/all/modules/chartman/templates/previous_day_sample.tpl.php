<table>
    <thead>
        <tr>
            <th>LABOURATORY</th>
            <th>INITIAL</th>
            <th>REPEAT</th>
            <th>FOLLOW UP</th>
            <th>MISSING</th>
            <th>TOTAL</th>
            <th>DAILY TARGET</th>
            <th>PERCENTAGE</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($items as $item): ?>
            <tr>
                <td><?php print $item['label']; ?></td>
                <td><?php print $item['initial']; ?></td>
                <td><?php print $item['repeat']; ?></td>
                <td><?php print $item['followup']; ?></td>
                <td><?php print $item['missing']; ?></td>
                <td><?php print $item['total']; ?></td>
                <td><?php print $item['target']; ?></td>
                <td><?php print $item['perc']; ?>%</td>
            </tr>
        <?php endforeach; ?>
    </tbody>
</table>
