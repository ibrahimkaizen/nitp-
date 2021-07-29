<table>
    <thead>
        <tr>
            <th></th>
            <th>Yesterday</th>
            <th>Cumulative</th>
            <th>%</th>
        </tr>
    </thead>
    <tbody>
        <?php $tt = 0; foreach ($items as $item): ?>
            <?php
                $yes_value = str_replace(',', '', trim($item['node']['Yesterday']));
                $cum_value = str_replace(',', '', trim($item['node']['Cumulative']));
                $percent = ($cum_value/$cum_total)*100;
            ?>
            <tr>
                <td><?php print $item['node']['name']; ?></td>
                <td><?php print number_format($yes_value); ?></td>
                <td><?php print number_format($cum_value); ?></td>
                <td><?php print round($percent, 1); ?>%</td>
            </tr>
            <?php $tt += $percent; ?>
        <?php endforeach; ?>
    </tbody>
    <tfoot>
        <tr>
            <td>Total</td>
            <td><?php print number_format($yes_total); ?></td>
            <td><?php print number_format($cum_total); ?></td>
            <td><?php print $tt; ?>%</td>
        </tr>
    </tfoot>
</table>
