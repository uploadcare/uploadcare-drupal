# Drupal Module for Uploadcare

This is a plugin for [Drupal][3] to work with [Uploadcare][1]

It's based on a [uploadcare-php][4] library.

## Requirements

- Drupal 7.x+
- PHP 5.2+
- php-curl

## Install 

Clone module from git to your plugins directory:

    git clone git://github.com/uploadcare/uploadcare-drupal.git modules/uploadcare --recursive

Activate plugin at "Modules" section.

Follow "Configure" link for the Uploadcare module and provide public and secret keys.

## Usage

Create or edit a new Content Type inside your Drupal.

Select "Manage fields".

Add new field and set "Field Type" equal to Uploadcare widget and "Widget Type" field set to "Uploadcare".

Save new field and you will be redirected to Uploadcare field settings.

You can choose will be this an image or not and select all the CDN operations for the image.

Just upload an image with new field and it will be displayed for the new content.

[More information on file operations can be found here][2]

## Downloads

**1.0.2** ([Download](https://ucarecdn.com/11f02ead-fd66-4108-aedd-b3394b324d73/uploadcare-drupal_1.0.2.zip))
* Bugfixes

**1.0.1** ([Download](https://ucarecdn.com/db0033ad-c84a-498e-8ca9-c01e6d49510a/uploadcare-drupal_1.0.1.zip))
* Bugfixes

[1]: https://uploadcare.com/
[2]: https://uploadcare.com/documentation/reference/basic/cdn.html
[3]: http://drupal.org/
[4]: https://github.com/uploadcare/uploadcare-php
