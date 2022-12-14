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
 * config.inc
 * 
 * ApiGrave configuration settings.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2021, 2024, 5 Mode     
 */

define('DEBUG', false);
 
define('APP_NAME', "Api Grave");
define('APP_TITLE', "Api Grave, your api our grave..");

define('APP_SPLASH', true);

define('APP_HOST', "yourapigrave.com");
define('APP_PATH', "var/www/YourApiGrave/Public");
define('APP_ERROR_PATH', "var/www/YourApiGrave/Private/error");
define('APP_API_PATH', "var/www/YourApiGrave/Private/api");

// Default Locale, in two letters format
define('APP_LOCALE', "EN");

define('CACHE_HOST', "127.0.0.1");
define('CACHE_PORT', "11211");
define('CACHE_EXPIRE', 45);
define('CACHE_APP_PREFIX', "APIG_tosqefv0ct_");

$CONFIG = [

   'DEBUG' => false,

   'APP' => [
      'NAME' => "Api Grave",
      'TITLE' => "Api Grave, your api our grave..", 
      'SPLASH' => true,
      'HOST' => "yourapigrave.com", 
      'PATH' => "/var/www/YourApiGrave/Public",
      'ERROR_PATH' => "/var/www/YourApiGrave/Private/error",
      'API_PATH' => "/var/www/YourApiGrave/Private/api",
      'LOCALE' => "EN",
      ],

  'CACHE' => [
      'HOST' => "127.0.0.1",
      'PORT' => "11211",
      'EXPIRE' => 45,
      'APP_PREFIX' => "APIG_tosqefv0ct_",
      ]    
    
    ];  
