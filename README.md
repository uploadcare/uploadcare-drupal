# Drupal Module for Uploadcare

This is a plugin for [Drupal][3] to work with [Uploadcare][1]

It's based on a [uploadcare-php][4] library.

## Requirements

- Drupal 7.x+
- PHP 5.3+
- php-curl

## Install 

### From github

Clone module from git to your plugins directory:

    git clone git://github.com/uploadcare/uploadcare-drupal.git sites/default/modules/uploadcare --recursive
    
### Drupal git

	git clone http://git.drupal.org/sandbox/grayhound/1905848.git sites/default/modules/uploadcare --recursive
	git clone git://github.com/uploadcare/uploadcare-php.git sites/default/modules/uploadcare/uploadcare-php --recursive
	
### Using zip-package

Download the release from Downloads section and unzip it under "modules" directory.

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

**1.0.3** ([Download](https://ucarecdn.com/14c42caf-f5bd-4488-ab30-97b3b5079f3c/uploadcare-drupal_1.0.3.zip))
* Bugfixes

**1.0.2** ([Download](https://ucarecdn.com/11f02ead-fd66-4108-aedd-b3394b324d73/uploadcare-drupal_1.0.2.zip))
* Bugfixes

**1.0.1** ([Download](https://ucarecdn.com/db0033ad-c84a-498e-8ca9-c01e6d49510a/uploadcare-drupal_1.0.1.zip))
* Bugfixes

## Contributors

- [@grayhound](https://github.com/grayhound)
- [@dmitry-mukhin](https://github.com/dmitry-mukhin)
- [@dimaninc](https://github.com/dimaninc)

## Security issues

If you think you ran into something in Uploadcare libraries
which might have security implications, please hit us up at
[bugbounty@uploadcare.com](mailto:bugbounty@uploadcare.com)
or Hackerone.

We'll contact you personally in a short time to fix an issue
through co-op and prior to any public disclosure.

[1]: https://uploadcare.com/
[2]: https://uploadcare.com/documentation/cdn/
[3]: http://drupal.org/
[4]: https://github.com/uploadcare/uploadcare-php
