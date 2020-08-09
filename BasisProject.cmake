# ===============================================================================
# Copyright (c) 2020 Hypothermic IT
# All rights reserved.
#
# See COPYING file for license information.
# ===============================================================================

basis_project (
  # --------------------------------------------------------------------------
  # meta-data
  NAME             "Enlightenment"
  VERSION          "0.1.0"
  AUTHORS          "admin@hypothermic.nl"
  DESCRIPTION      "Extensible database software"
  VENDOR           "Hypothermic IT"
  PROVIDER_NAME    #<provider-name>
  PROVIDER_LOGO    #<provider-logo>
  PROVIDER_WEBSITE "http://www.hypothermic.nl/"
  DIVISION_NAME    #<division-name>
  DIVISION_LOGO    #<division-logo>
  DIVISION_WEBSITE #<division-website>
  COPYRIGHT        "2020 Hypothermic IT"
  LICENSE          "See COPYING file for license information."
  CONTACT          "M. Bakker <admin@hypothermic.nl>"
  TEMPLATE         "basis/1.4"

  DEPENDS
    glib-2.0
  OPTIONAL_DEPENDS
    #<optional-dependency>
  TEST_DEPENDS
    #<test-dependency>
  OPTIONAL_TEST_DEPENDS
    #<optional-test-dependency>
)
