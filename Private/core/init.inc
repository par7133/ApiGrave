<?php

/**
 * Copyright (c) 2016, 2024, 5 Mode
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither 5 Mode nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * init.inc
 * 
 * John Help initialization file.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2021, 2024, 5 Mode     
 */

use fivemode\fivemode\Cache;

error_reporting(E_ALL & ~ (E_WARNING | E_NOTICE | E_STRICT | E_DEPRECATED));  
ini_set('display_startup_errors',1);  
ini_set('display_errors',1);  
ini_set('log_errors',1);

define("CONFIG_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "config");

require CONFIG_PATH . DIRECTORY_SEPARATOR . "config.inc";
require CONFIG_PATH . DIRECTORY_SEPARATOR . "const.php.inc";

mb_internal_encoding("UTF-8");


// AUTOLOADER

define("CLASSES_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "classes");
define("INTERFACES_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "interfaces");

/**
 * Autoloader.
 * 
 * @param string $construct the name of the construct to load
 */
function autoloader($construct) {
  
  // For third-party libraries, eg. Pear
  if (!defined("PHP_INCLUDE_PATH")) {
    define("PHP_INCLUDE_PATH", ini_get("include_path"));
  }
  
  $constructParts = explode('\\', $construct);
  
  // estrapolate the path from the construct name
  $count = count($constructParts);
  if ($count>1) {
    $i = 0;
    $constructPath = $constructParts[0];
    for ($i=1; $i<($count-1); $i++) {
      $constructPath .= DIRECTORY_SEPARATOR . $constructParts[$i];
    }
    $construct = $constructParts[$i];
  }
  
  if (!stripos($construct, "interface")) {
    // if it is a class
  
    switch ($construct) {
      case "special_case":
        $incPath = PHP_INCLUDE_PATH . DIRECTORY_SEPARATOR . "path/to/special_case.php";
        break;
      case "QRcode":
        $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . "phpqrcode/qrlib.php";
        //echo "incPath = $incPath" . PHP_BR;
        break;
      default:
      
        if (isset($constructPath)) {
          $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . $constructPath . DIRECTORY_SEPARATOR . "class." . strtolower($construct) . ".inc";
        } else {
          $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . "class." . strtolower($construct) . ".inc";
        }
        
        break;
    }
    
  } else {
    // if it is an interface
    if (isset($constructPath)) {
      $incPath = INTERFACES_PATH . DIRECTORY_SEPARATOR  . $constructPath . DIRECTORY_SEPARATOR . strtolower($construct) . ".inc";
    } else {
      $incPath = INTERFACES_PATH . DIRECTORY_SEPARATOR . strtolower($construct) . ".inc";
    }  
  }
  
  if (is_readable($incPath)) {
    //echo "$incPath is readable" . PHP_BR;
    require $incPath;
  }
  
}
spl_autoload_register("autoloader", true, true);

// FUNCTIONS

define("FUNCTIONS_PATH", __DIR__.DIRECTORY_SEPARATOR."..".DIRECTORY_SEPARATOR."functions");

require FUNCTIONS_PATH . DIRECTORY_SEPARATOR . "func.various.inc";

// ERROR HANDLING AND LOGGING

if (DEBUG) {
  error_reporting(E_ALL | E_STRICT);  
  ini_set('display_startup_errors',1);  
  ini_set('display_errors',1);
  ini_set('log_errors',1); 
} else {
  error_reporting(E_ALL & ~ (E_WARNING | E_NOTICE | E_STRICT | E_DEPRECATED));  
  ini_set('display_startup_errors',0);  
  ini_set('display_errors',0);  
  ini_set('log_errors',1); 
}

// Set no cache headers
// for HTTP/1.0 clients
header("Expires: 0");
header("Pragma: no-cache");
// HTTP/1.1 support
header("Cache-Control: private,no-cache,max-age=0,s-maxage=0,must-revalidate");

// SHUTDOWN 

/**
 * Shutdown callback.
 * 
 * @return void
 */
function shutdownCallback() {
  
  //Err::setLogOnlyHandlers();
  
  if (Cache::issetInstance()) {  
    //For non-persistent connections only
    //$cache = &Cache::getInstance();
    //$cache->close();

    Cache::unsetInstance();
  }

}
register_shutdown_function("shutdownCallback");