<?php

/**
 * @file
 * Displays all active items.
 */

/**
 * Extension of CurrentSearchItem that displays all active items.
 */
class CurrentSearchItemActiveLinks extends CurrentSearchItem {

  /**
   * Implements CurrentSearchItem::execute().
   */
  public function execute(FacetapiAdapter $adapter) {
    $items = array();

    // Makes sure facet builds are initialized.
    $adapter->processFacets();

    // Initializes links attributes, adds rel="nofollow" if configured.
    $attributes = ($this->settings['nofollow']) ? array('rel' => 'nofollow') : array();
    $attributes += array('class' => array('current-search-links'));

    $search_keys = $adapter->getSearchKeys();
    $keys = array();

    // Adds the keywords if any were passed.
    if ($this->settings['keys'] && $search_keys && $search_keys != t('[all items]')) {
      $keys = array($search_keys);
      if (!$this->settings['keys_whole']) {
        preg_match_all('/[^\s]*"[^"]*"|\S+/', $search_keys, $keys);
        $keys = $keys[0];
      }

      foreach ($keys as $i => $key) {
        $params = $adapter->getUrlProcessor()->getParams();
        $keys_copy = $keys;
        unset($keys_copy[$i]);
        $new_search_terms = implode(' ', $keys_copy);

        $path = $adapter->getSearchPath();
        if (isset($this->settings['arguments']) && is_numeric($this->settings['arguments'])) {
          // Change the appropriate URL argument
          $arg_position = $this->settings['arguments'];
          $args = arg();
          if (!empty($args[$arg_position])) {
            $args[$arg_position] = $new_search_terms;
          }
          $path = implode('/', $args);
        }
        else {
          // Change the search filter parameter
          $params[$this->settings['search_param']] = $new_search_terms;
        }

        // Clean up parameters if pretty paths are enabled.
        $urlProcessor = $adapter->getUrlProcessor();
        if (module_exists('facetapi_pretty_paths') && $urlProcessor instanceof FacetapiUrlProcessorPrettyPaths) {
          unset($params[$adapter->getUrlProcessor()->getFilterKey()]);
          // Retrieve the full path from the url processor.
          $path = $urlProcessor->getFullPath();
        }

        // Renders the active link.
        $items[] = array(
          '#theme' => 'facetapi_link_active__current_search_links',
          '#text' => check_plain($key),
          '#path' => $path,
          '#options' => array(
            'attributes' => $attributes,
            'html' => TRUE,
            'query' => $params,
          ),
        );
      }
    }
    else {
      if ($search_keys) {
        $items[] = array('#markup' => check_plain($search_keys));
      }
    }

    // Gets the translated pattern with token replacements in tact.
    $pattern = $this->translate('pattern', $this->settings['pattern']);

    // Adds active facets to the current search block.
    if (!$this->settings['hide_facets']) {
      foreach ($adapter->getAllActiveItems() as $item) {
        // Adds adapter to the active item for token replacement.
        $item['adapter'] = $adapter;

        // Builds variables to pass to theme function.
        $data = array('facetapi_active_item' => $item);

        // Renders the active facets link.
        $items[] = array(
          '#theme' => 'facetapi_link_active__current_search_links',
          '#text' => token_replace($pattern, $data),
          '#path' => $this->getFacetPath($item, $adapter),
          '#options' => array(
            'attributes' => $attributes,
            'html' => TRUE,
            'query' => $this->getQueryString($item, $adapter),
          ),
          '#facet_field' => $item['field alias'],
        );
      }
    }
    // If there are items, return the render array.
    if ($items) {
      $classes = ($this->settings['css']) ? current_search_get_classes($this->settings['classes']) : array();

      $context = array(
        'keys_raw' => $search_keys,
        'keys_splitted' => $keys,
        'plugin' => $this,
        'adapter' => $adapter,
      );
      drupal_alter('current_search_links_active_items', $items, $context);

      return array(
        '#theme' => 'item_list',
        '#items' => array_map('drupal_render', $items),
        '#attributes' => array('class' => $classes),
      );
    }
  }

  /**
   * Implements CurrentSearchItem::settingsForm().
   */
  public function settingsForm(&$form, &$form_state) {
    $form['pattern'] = array(
      '#type' => 'textfield',
      '#title' => t('Pattern'),
      '#default_value' => $this->settings['pattern'],
      '#description' => t('The pattern used to render active items in the list. Token replacement patterns are allowed.'),
      '#maxlength' => 255,
    );

    $form['keys'] = array(
      '#type' => 'checkbox',
      '#title' => t('Append the keywords passed by the user to the list'),
      '#default_value' => $this->settings['keys'],
    );

    $form['keys_whole'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add the keys as a phrase to remove it at once'),
      '#default_value' => isset($this->settings['keys_whole']) ? $this->settings['keys_whole'] : '',
      '#states' => array(
        'visible' => array(
          ':input[name="plugin_settings[' . $this->name . '][keys]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['hide_facets'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide active facet items'),
      '#default_value' => isset($this->settings['hide_facets']) ? $this->settings['hide_facets'] : '',
    );

    $form['css'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add CSS classes to wrapper element'),
      '#default_value' => $this->settings['css'],
    );

    $form['classes'] = array(
      '#type' => 'textfield',
      '#title' => t('CSS classes'),
      '#default_value' => $this->settings['classes'],
      '#description' => t('A comma separated list of CSS classes.'),
      '#maxlength' => 128,
      '#states' => array(
        'visible' => array(
          ':input[name="plugin_settings[' . $this->name . '][css]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['nofollow'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prevent crawlers from following active item links'),
      '#default_value' => $this->settings['nofollow'],
      '#description' => t('Add the <code>rel="nofollow"</code> attribute to active item links to maximize SEO by preventing crawlers from indexing duplicate content and getting stuck in loops.'),
    );

    $form['arguments'] = array(
      '#type' => 'textfield',
      '#size' => 8,
      '#maxlength' => 128,
      '#title' => 'URL argument position',
      '#description' => t('Normally, this can be left empty. This becomes useful if you use a contextual filter instead of exposed filters for your search terms (for example, URLs like <code>/search/search+terms</code> rather than <code>/search?search_api_views_fulltext=some+terms</code>), enter the position of the search terms in the URL here. 0 is the first argument, so enter 1 for a URL like <code>/search/some+terms</code>, 2 for a URL like <code>/search/advanced_search/some+terms</code>, etc.'),
      '#element_validate' => array('element_validate_number'),
      '#filters' => array('trim', 'uppercase'),
      '#default_value' => $this->settings['arguments'],
    );

    $form['search_param'] = array(
      '#type' => 'textfield',
      '#size' => 16,
      '#maxlength' => 128,
      '#title' => 'Search parameter',
      '#description' => t('Normally, this is "search_api_views_fulltext". But if you customized your search, the search parameter is maybe "find" or just "search". E.g. <code>/search?find=some+text</code>'),
      '#default_value' => $this->settings['search_param'],
    );

    // Adds token tree.
    $form['tokens'] = $this->getTokenTree(array('facetapi_active'));
  }

  /**
   * Implements CurrentSearchItem::getDefaultSettings().
   */
  public function getDefaultSettings() {
    return array(
      'pattern' => '[facetapi_active:active-value]',
      'keys' => TRUE,
      'css' => FALSE,
      'classes' => '',
      'nofollow' => TRUE,
      'keys_whole' => FALSE,
      'hide_facets' => FALSE,
      'attributes' => '',
      'arguments' => '',
      'search_param' => 'search_api_views_fulltext',
    );
  }
}

