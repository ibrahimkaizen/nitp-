
<div>
    <h3>Case is Contact of another case</h3>
    <table>
        <thead>
            <tr>
                <th></th>
                <th>Number</th>
                <th>Percent</th>
            </tr>
        </thead>
        <tbody>
        <?php if ($c):?>
            <?php foreach ($c as $value): ?>
                <tr>
                    <td><?php print $value[0]; ?> </td>
                    <td><?php print $value[1];?> </td>
                    <td><?php print $value[2];?>% </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
        </tbody>
        <tfoot>
            <tr>
                <td>Total</td>
                <td><?php print $total[0]; ?></td>
                <td><?php print $total[1]; ?>% </td>
            </tr>
        </tfoot>
    </table>
</div>

