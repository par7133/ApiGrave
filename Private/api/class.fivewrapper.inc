<?php

/**
 * Copyright (c) 2016, 2024, 5 Mode
 * All rights reserved.
 * 
 * This file is part of ApiGrave.
 *
 * ApiGrave is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ApiGrave is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.  
 * 
 * You should have received a copy of the GNU General Public License
 * along with ApiGrave. If not, see <https://www.gnu.org/licenses/>.
 *
 * class.classwrapper.inc
 * 
 * The ClassWrapper class.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2024, 5 Mode     
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace fivemode\fivemode;

/**
 * ClassWrapper
 *
 * ClassWrapper class
 *
 * @package  Wrappers
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  1.0
 * @access   public
 */
final class FiveWrapper
{

  private static $value = '5'; 

  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }

  public static function set5Mode($v): bool
  {
    self::$value = $v;
    return true;
  }
  
  public static function get5Mode()
  {
    return self::$value;
  }
}
