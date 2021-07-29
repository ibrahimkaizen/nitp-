<?php if($items): ?>
<table>
    <thead>
        <tr>
            <th></th>
            <th>Yesterday</th>
            <th>Cumulative</th>
        </tr>
    </thead>
    <tbody>
        <?php $tt = 0; foreach ($items as $item): ?>
            <?php
                $yes_value = str_replace(',', '', trim($item['node']['Yesterday']));
                $cum_value = str_replace(',', '', trim($item['node']['Cumulative']));
            ?>
            <tr>
                <td><?php print $item['node']['name']; ?></td>
                <td><?php print number_format($yes_value); ?></td>
                <td><?php print number_format($cum_value); ?></td>
            </tr>
        <?php endforeach; ?>
    </tbody>
    <tfoot>
        <tr>
            <td>Total</td>
            <td><?php print number_format($yes_total); ?></td>
            <td><?php print number_format($cum_total); ?></td>
        </tr>
    </tfoot>
</table>
<?php endif; ?>
