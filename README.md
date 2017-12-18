# Archived

Repo archived instead of deleted for posterity. This use case has been resolved with the [discoverygarden Islandora Serials Solution Pack](https://github.com/discoverygarden/islandora_solution_pack_serial) module.

******

# Scrapbook

**Work in Progress: Not for use in production.**

## Introduction

Tweaking the Islandora [Newspaper](https://github.com/Islandora/islandora_solution_pack_newspaper) solution pack to display paged content with 3+ nested layers.  
The primary difference is the removal of the [dateIssued](http://books.xmlschemata.org/relaxng/ch19-77049.html) parameter in the `issue` object, and further development of the [isSequenceOf](http://books.xmlschemata.org/relaxng/ch19-77247.html) parameter in its place for sequencing and navigation.    

**Current Status**

* Islandora Scrapbook appears as solution pack in repository
* Ability to create new Scrapbook parent object
* In process: Iterative code cleanup through object creation process until no expected action breaks the site

**Next Steps**

* Develop sequence rules for `issue` object
* Determine final naming conventions to avoid conflict with Islandora Paged Content object names
* Finalize documentation according to Islandora module recommendations
* Adapt theming towards book-like navigation from visual perspective

**Why didn't you open an issue?**

At present this project appears to be an individualized customization of the Newspaper that does not warrant an entirely new " Islandora Scrapbook Solution Pack."  
It is being developed from the "making a solution pack" point of view only to follow best practices and allow for future expansion, if desired.

Newspaper documentation below for underlying structural reference.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)
* [Islandora Paged Content](https://github.com/islandora_paged_content)
* [Islandora OCR](https://github.com/Islandora/islandora_ocr)
* [Islandora Large Image Solution Pack](https://github.com/Islandora/islandora_solution_pack_large_image)
* [Islandora Openseadragon](https://github.com/islandora_openseadragon) (optional)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Select configuration options for page derivatives, Parent Solr Field, and select a viewer for the issue view and page view in  Administration » Islandora » Solution pack configuration » Newspapers (admin/islandora/solution_pack_config/newspaper).


![Configuration](https://camo.githubusercontent.com/00b3d34d5927b733689ce0d1598a79c832082937/687474703a2f2f692e696d6775722e636f6d2f56764b6a6479462e706e67)

## Documentation
:warning: <br/>Deleting a newspaper object directly (Manage > Properties >  Delete Newspaper) will delete all its child Issue objects, and their associated Page objects. Highlighted in red in this diagram shows all that will be deleted if the newspaper Locusta Newspaper is deleted. 
+![newspaper_diagram](https://user-images.githubusercontent.com/2738244/30652457-6ea939e0-9df6-11e7-851b-d298ca1e631b.png)

However, deleting a newspaper via its parent collection (by deleting the collection or by using "Delete members of this collection") will cause that newspaper's Issue objects to be orphaned.

Further documentation for this module is available at [our wiki](https://wiki.duraspace.org/display/ISLANDORA/Newspaper+Solution+Pack).

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [Jared Whiklo](https://github.com/whikloj)

## Development

If you would like to contribute to this module, please check out [CONTRIBUTING.md](CONTRIBUTING.md). In addition, we have helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the [Islandora.ca](http://islandora.ca) site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
