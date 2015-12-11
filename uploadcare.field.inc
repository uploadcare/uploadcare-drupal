<?php
/**
 * @file
 * Uploadcare.field.inc
 * Uploadcare widget field setup, handling, etc...
 */

/**
 * Connect external library. Please read more at:
 * https://github.com/uploadcare/uploadcare-php .
 */
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/Api.php';
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/File.php';
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/FileIterator.php';
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/Group.php';
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/Uploader.php';
require_once drupal_get_path('module', 'uploadcare') . '/uploadcare-php/src/Uploadcare/Widget.php';

/**
 * Implements hook_field_info().
 */
function uploadcare_field_info() {
  return array(
    'uploadcare' => array(
      'label' => t('Uploadcare widget'),
      'description' => t('Uploadcare widget'),
      'default_widget' => 'uploadcare_widget',
      'default_formatter' => 'uploadcare_formatter',
    ),
  );
}

/**
 * Settings form.
 */
function uploadcare_field_settings_form($field, $instance, $has_data) {
  $settings = $field['settings'];
  // Is image checkbox.
  // Used to define if file should be displayed as an image or an url for file.
  $form['is_image'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is it an image?'),
    '#required' => FALSE,
    '#default_value' => isset($field['settings']['is_image']) ? $field['settings']['is_image'] : FALSE,
    '#description' => t('If the uploaded file is an image you will be able to use file operations'),
  );

  // Image operations field.
  // Find more information at https://uploadcare.com/documentation/cdn/.
  // Crop checkbox. Used with "is_image" checkbox. Tries to apply crop settings.
  $form['crop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Crop'),
    '#default_value' => isset($field['settings']['crop']) ? $field['settings']['crop'] : FALSE,
  );
  // Crop width.
  $form['crop_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Crop width'),
    '#default_value' => isset($field['settings']['crop_width']) ? $field['settings']['crop_width'] : NULL,
  );

  // Crop height.
  $form['crop_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Crop height'),
    '#default_value' => isset($field['settings']['crop_height']) ? $field['settings']['crop_height'] : NULL,
  );

  // Center crop.
  $form['crop_center'] = array(
    '#type' => 'checkbox',
    '#title' => t('Center crop?'),
    '#default_value' => isset($field['settings']['crop_center']) ? $field['settings']['crop_center'] : FALSE,
  );

  // Crop fill color.
  $form['crop_fill_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Crop fill color'),
    '#default_value' => isset($field['settings']['crop_fill_color']) ? $field['settings']['crop_fill_color'] : NULL,
  );

  // "Resize" checkbox.
  // Used with "is_image" checkbox.
  // Tries to apply resize settings.
  $form['resize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Resize'),
    '#default_value' => isset($field['settings']['resize']) ? $field['settings']['resize'] : FALSE,
  );

  // Resize width.
  $form['resize_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Resize width'),
    '#default_value' => isset($field['settings']['resize_width']) ? $field['settings']['resize_width'] : NULL,
  );

  // Resize height.
  $form['resize_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Resize height'),
    '#default_value' => isset($field['settings']['resize_height']) ? $field['settings']['resize_height'] : NULL,
  );

  // "Scale crop" checkbox.
  // Used with "is_image" checkbox.
  // Tries to apply "scale crop" settings.
  $form['scale_crop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scale crop'),
    '#default_value' => isset($field['settings']['scale_crop']) ? $field['settings']['scale_crop'] : FALSE,
  );

  // Scale crop width.
  $form['scale_crop_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Scale crop width'),
    '#default_value' => isset($field['settings']['scale_crop_width']) ? $field['settings']['scale_crop_width'] : NULL,
  );

  // Scale crop height.
  $form['scale_crop_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Resize crop height'),
    '#default_value' => isset($field['settings']['scale_crop_height']) ? $field['settings']['scale_crop_height'] : NULL,
  );

  // Center scale crop.
  $form['scale_crop_center'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scale center crop?'),
    '#default_value' => isset($field['settings']['scale_crop_center']) ? $field['settings']['scale_crop_center'] : FALSE,
  );

  // Apply flip effect to image.
  $form['flip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Flip image?'),
    '#default_value' => isset($field['settings']['flip']) ? $field['settings']['flip'] : FALSE,
  );

  // Apply grayscale effect to image.
  $form['grayscale'] = array(
    '#type' => 'checkbox',
    '#title' => t('Grayscale image?'),
    '#default_value' => isset($field['settings']['grayscale']) ? $field['settings']['grayscale'] : FALSE,
  );

  // Apply invert effect to image.
  $form['invert'] = array(
    '#type' => 'checkbox',
    '#title' => t('Invert image?'),
    '#default_value' => isset($field['settings']['invert']) ? $field['settings']['invert'] : FALSE,
  );

  // Apply mirror effect to image.
  $form['mirror'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mirror image?'),
    '#default_value' => isset($field['settings']['mirror']) ? $field['settings']['mirror'] : FALSE,
  );

  // Apply stretch off effect to image.
  $form['stretch_off'] = array(
    '#type' => 'checkbox',
    '#title' => t('Stretch off?'),
    '#default_value' => isset($field['settings']['stretch_off']) ? $field['settings']['stretch_off'] : FALSE,
  );

  return $form;
}

/**
 * Fields validation and file saving.
 */
function uploadcare_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $item) {
    if ($item['uploadcare']) {
      // Get publickey and secretkey from Uploadcare module settings.
      $public_key = variable_get('uploadcare_public_key');
      $secret_key = variable_get('uploadcare_secret_key');

      // File_id from the form.
      $file_id = $item['uploadcare'];

      // Start to work with api.uploadcare.com
      $api = new Uploadcare\Api($public_key, $secret_key, 'PHP Uploadcare Drupal');

      // Get file instance using API.
      $file = $api->getFile($file_id);

      // Store file to be saved at CDN (ucarecdn.com)
      $file->store();
      $filename = $file->data['original_filename'];

      // Insert some file essentials.
      db_query('INSERT INTO {uploadcare} VALUES (:file_id, :filename)', array(':file_id' => $file_id, ':filename' => $filename));
    }
  }
}

/**
 * Implements hook_field_widget_info().
 */
function uploadcare_field_widget_info() {
  return array(
    'uploadcare' => array(
      'label' => t('Uploadcare'),
      'field types' => array('uploadcare'),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function uploadcare_field_formatter_info() {
  return array(
    'uploadcare_formatter' => array(
      'label' => t('Uploadcare formatter'),
      'field types' => array('uploadcare'),
    ),
  );
}

/**
 * Uploadcare field widget postfix. Used to display Uploadcare widget itself.
 */
function uploadcare_field_widget_form_postfix($file_id, $settings) {
  return uploadcare_get_view_html($file_id, $settings);
}

/**
 * Implements hook_field_widget_form().
 */
function uploadcare_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  switch ($instance['widget']['type']) {
    case 'uploadcare':
      $element['uploadcare'] = array(
        '#prefix' => uploadcare_field_widget_form_prefix(),
        '#suffix' => @uploadcare_field_widget_form_postfix($items[$delta]['uploadcare'], $field['settings']),
        '#type' => 'textfield',
        '#title' => check_plain($element['#title']),
        '#description' => check_plain($element['#description']),
        '#default_value' => @$items[$delta]['uploadcare'],
        '#required' => $element['#required'],
        '#weight' => isset($element['#weight']) ? $element['#weight'] : 0,
        '#delta' => $delta,
        '#attributes' => array(
          'role' => 'uploadcare-uploader',
          'style' => 'display: none;',
        ),
      );
      break;
  }
  return $element;
}

/**
 * Get a prefix with script.
 */
function uploadcare_field_widget_form_prefix() {
  $public_key = variable_get('uploadcare_public_key');
  $secret_key = variable_get('uploadcare_secret_key');
  $api = new Uploadcare\Api($public_key, $secret_key);
  return $api->widget->getScriptTag(Uploadcare\Widget::version);
}

/**
 * Implements hook_field_is_empty().
 */
function uploadcare_field_is_empty($item, $field) {
  if (empty($item['uploadcare'])) {
    return TRUE;
  }

  return null;
}

/**
 * Display file.
 */
function uploadcare_get_view_html($file_id, $settings) {
  // If file is not uploaded - display nothing.
  if (!$file_id) {
    return '';
  }

  // Get publickey and secret key from Uploadcare module settings.
  $public_key = variable_get('uploadcare_public_key');
  $secret_key = variable_get('uploadcare_secret_key');

  // Connect to api.uploadcare.com
  $api = new Uploadcare\Api($public_key, $secret_key);

  // Will be used further to define final html.
  $is_image = $settings['is_image'];

  // Collect crop settings for field.
  $crop = isset($settings['crop']) ? $settings['crop'] : FALSE;
  $crop_width = isset($settings['crop_width']) ? $settings['crop_width'] : NULL;
  $crop_height = isset($settings['crop_height']) ? $settings['crop_height'] : NULL;
  $crop_center = isset($settings['crop_center']) ? $settings['crop_center'] : NULL;
  $crop_fill_color = isset($settings['crop_fill_color']) ? $settings['crop_fill_color'] : FALSE;

  // Collect resize settings for field.
  $resize = isset($settings['resize']) ? $settings['resize'] : FALSE;
  $resize_width = isset($settings['resize_width']) ? $settings['resize_width'] : NULL;
  $resize_height = isset($settings['resize_height']) ? $settings['resize_width'] : NULL;

  // Collect scale_crop settings for field.
  $scale_crop = isset($settings['scale_crop']) ? $settings['scale_crop'] : FALSE;
  $scale_crop_width = isset($settings['scale_crop_width']) ? $settings['scale_crop_width'] : NULL;
  $scale_crop_height = isset($settings['scale_crop_height']) ? $settings['scale_crop_height'] : NULL;
  $scale_crop_center = isset($settings['scale_crop_center']) ? $settings['scale_crop_center'] : FALSE;

  // Collect effects for field.
  $flip = isset($settings['flip']) ? $settings['flip'] : FALSE;
  $grayscale = isset($settings['grayscale']) ? $settings['grayscale'] : FALSE;
  $invert = isset($settings['invert']) ? $settings['invert'] : FALSE;
  $mirror = isset($settings['mirror']) ? $settings['mirror'] : FALSE;
  $stretch_off = isset($settings['stretch_off']) ? $settings['stretch_off'] : FALSE;

  $file = $api->getFile($file_id);
  $result = db_query('SELECT filename FROM {uploadcare} where file_id = :file_id', array(':file_id' => $file_id));
  foreach ($result as $record) {
    $filename = $record->filename;
  }

  // Display file as an image with all image operations applied.
  if ($is_image) {
    // Clone file object to use original object further.
    $original_file = clone $file;

    // Apply crop settings if "Crop" checkbox is used.
    if ($crop) {
      $file = $file->crop($crop_width, $crop_height, $crop_center, $crop_fill_color);
    }

    // Apply resize settings if "Resize" checkbox is used.
    if ($resize) {
      $file = $file->resize($resize_width, $resize_height);
    }

    // Apply scale crop settings if "Scale Crop" checkbox is used.
    if ($scale_crop) {
      $file = $file->scaleCrop($scale_crop_width, $scale_crop_height, $scale_crop_center);
    }

    // Apply flip effect.
    if ($flip) {
      $file = $file->effect('flip');
    }

    // Apply grayscale effect.
    if ($grayscale) {
      $file = $file->effect('grayscale');
    }

    // Apply invert effect.
    if ($invert) {
      $file = $file->effect('invert');
    }

    // Apply mirror effect.
    if ($mirror) {
      $file = $file->effect('mirror');
    }

    // Apply stertch off.
    if ($stretch_off) {
      $file = $file->op('stretch/off');
    }

    // Final html to return.
    // An image with all file operations with a link to the original file.
    $html = sprintf('<a href="%s">%s</a>', $file->getUrl($filename), $file->getImgTag($filename));
  }
  else {
    // Just a link to the file with original filename.
    $html = sprintf('<a href="%s">%s</a>', $file->getUrl($filename), $filename);
  }
  return $html;
}

/**
 * Implements hook_field_formatter_view().
 */
function uploadcare_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $settings = $field['settings'];

  $elements = array();
  foreach ($items as $delta => $item) {
    $file_id = $item['uploadcare'];

    $html = uploadcare_get_view_html($file_id, $settings);

    $elements[$delta] = array(
      '#markup' => $html,
    );
  }
  return $elements;
}
