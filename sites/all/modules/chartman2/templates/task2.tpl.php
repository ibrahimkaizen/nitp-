<div class="chartman2_task2a">
    <h3>Gender distribution of positive cases</h3>
    <canvas id="chartman2_task2a"></canvas>
</div>


<!-- B -->
<div class="chartman2_task2b">
    <h3>Age and gender pyramid</h3>
    <canvas id="chartman2_task2b"></canvas>
</div>

<!-- C -->
<div>

    <h3>Age Overview Table</h3>
    <table>
        <thead>
            <tr>
                <th>Gender</th>
                <th>Number</th>
                <th>Percent</th>
            </tr>
        </thead>
        <tbody>
        <?php if ($c):?>
            <?php foreach ($c[0] as $id => $value): ?>
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
                <td><?php print $c[1]; ?></td>
                <td><?php print $c[2]; ?>% </td>
            </tr>
        </tfoot>
    </table>
</div>


<!-- D -->
<div>
    <h3>Age Range Overview Table</h3>
    <table>
        <thead>
            <tr>
                <th>Age Category</th>
                <th>Number</th>
                <th>Percent</th>
            </tr>
        </thead>
        <tbody>
        <?php if ($d):?>
            <?php foreach ($d[0] as $id => $value): ?>
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
                <td><?php print $d[1]; ?></td>
                <td><?php print $d[2]; ?>% </td>
            </tr>
        </tfoot>
    </table>
</div>