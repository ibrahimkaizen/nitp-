<table>
    <thead>
        <tr>
            <th></th>
            <th>Yesterday</th>
            <th>Cummulative</th>
        </tr>
    </thead>
    <tbody>
        <?php $yesterday = $cumm = 0 ; ?>
        <?php foreach ($items as $item): ?>
            <?php
                $yes_value = str_replace(',', '', trim($item['node']['Yesterday']));
                $cum_value = str_replace(',', '', trim($item['node']['Cummulative']));
            ?>
            <tr>
                <td><?php print $item['node']['name']; ?></td>
                <td><?php print number_format($yes_value); ?></td>
                <td><?php print number_format($cum_value); ?></td>
            </tr>
            <?php
                $yesterday += $yes_value;
                $cumm += $cum_value;
            ?>
        <?php endforeach; ?>
    </tbody>
    <tfoot>
        <tr>
            <td>Total</td>
            <td><?php print number_format($yesterday); ?></td>
            <td><?php print number_format($cumm); ?></td>
        </tr>
    </tfoot>
</table>
