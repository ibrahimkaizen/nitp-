
<!-- A -->
<div>
    <h3>LGA distribution of positive cases</h3>
    <table>
        <thead>
            <tr>
                <th>LGA</th>
                <th>Number</th>
                <th>Percent</th>
            </tr>
        </thead>
        <tbody>
        <?php if ($a):?>
            <?php foreach ($a[0] as $id => $value): ?>
                <tr>
                    <td><?php print $value['age']; ?> </td>
                    <td><?php print $value['number'];?> </td>
                    <td><?php print $value['percent'];?>% </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
        </tbody>
        <tfoot>
            <tr>
                <td>Total</td>
                <td><?php print $a[1]; ?></td>
                <td><?php print $a[2]; ?>% </td>
            </tr>
        </tfoot>
    </table>
</div>


<!-- B -->
<div>
    <h3>Test Positivity Rate (TPR) by LGA</h3>
    <canvas id="chartman2_task5b"></canvas>
</div>


<!-- C -->

<div>
    <h3>Distribution of positive cases by nationality</h3>
    <table>
        <thead>
            <tr>
                <th>Nationality</th>
                <th>Number</th>
                <th>Percent</th>
            </tr>
        </thead>
        <tbody>
        <?php if ($c):?>
            <?php foreach ($c[0] as $id => $value): ?>
                <tr>
                    <td><?php print $value['nationality']; ?> </td>
                    <td><?php print $value['number'];?> </td>
                    <td><?php print $value['percent'];?>% </td>
                </tr>
            <?php endforeach; ?>
        <?php endif; ?>
        </tbody>
        <tfoot>
            <tr>
                <td>Total</td>
                <td><?php print $c[1]; ?></td>
                <td><?php print $c[2]; ?>% </td>
            </tr>
        </tfoot>
    </table>
</div>
