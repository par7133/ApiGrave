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
 * index.php
 * 
 * The index file.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2024, the Open Gallery's contributors     
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

require "../Private/core/init.inc";

use fivemode\fivemode\Cache;

// FUNCTION AND VARIABLE DECLARATIONS

//$scriptPath = APP_SCRIPT_PATH;
$env = [];
$methods = [];


function eval_ex_handler(Throwable $exception) {
  global $methods;
  global $url;
  
  echo("<h1>This is a bit of doc for $url:</h1>");
  echo("<br><br>");
  echo($methods[$url]["doc"]);
}

// READING METHODS FROM THE API PATH

// Reading from the cache first
$cache = &Cache::getInstance();

$cacheKey = md5("CALL spGetMethods();");
$methods = false; //$cache->getJ($cacheKey);
if (!$methods) {
  
  chdir(APP_API_PATH);
  
  $pattern =  "*.inc";
  $apiPaths = glob($pattern);
  
  //print_r($apiPaths);
  
  $eni=0;
  foreach($apiPaths as $apiPath) {
    
    $ipos = strripos($apiPath, PHP_SLASH);
    if ($ipos !== false) {
      $apiPath = substr($apiPath, $ipos);
    }
    $apiPath = APP_API_PATH . DIRECTORY_SEPARATOR . $apiPath;
  
    $apistr = file_get_contents($apiPath);

    // Parsing for the api namespace.. 
    $matches = []; 
    $regstr = '/namespace\s(?<namespace>[\w\-\\\]+)\;/';
    if (preg_match_all($regstr, $apistr, $matches, PREG_SET_ORDER) !== false) {
      $env[$eni]['namespace'] = (string)$matches[0]["namespace"];
    } 
    if (empty($env[$eni]['namespace'])) {
      $env[$eni]['namespace'] = "-";
    }

    // Parsing for the api classname..
    $matches = []; 
    $regstr = '/class\s(?<classname>[\w\-]+)\s/';
    if (preg_match_all($regstr, $apistr, $matches, PREG_SET_ORDER) !== false) {
      $env[$eni]['classname'] = (string)$matches[0]["classname"];
    }
    if (empty($env[$eni]['classname'])) {
      $env[$eni]['classname'] = "-";
    }
    
    //echo("namespace=".$env[$eni]['namespace']."<br>");
    //echo("classname=".$env[$eni]['classname']."<br>");
    
    $matches = [];
    $regstr = '/(?<func_header>(?<visibility>private|public)?\s?(?<func_modifier>static)?\s?function\s(?<name>\&?[\w\-]{2,25})\((?<param_defs>(?<param_def1>\s?(?<optional_flag1>\?)?(?<param_type1>[a-z]{3,8})?\s?(?<reference_flag1>[\&]{0,1})?(?<param_name1>\$[\w\-]{1,20})\s?(?<default_value1>\=\s?[\w\-\']{1,128})?\s?\,?\s?)?(?<param_def2>\s?(?<optional_flag2>\?)?(?<param_type2>[a-z]{3,8})?\s?(?<reference_flag2>\&)?(?<param_name2>\$[\w\-]{1,20})\s?(?<default_value2>\=\s?[\w\-\']{1,128})?\s?\,?\s?)?(?<param_def3>\s?(?<optional_flag3>\?)?(?<param_type3>[a-z]{3,8})?\s?(?<reference_flag3>\&)?(?<param_name3>\$[\w\-]{1,20})\s?(?<default_value3>\=\s?[\w\-\']{1,128})?\s?\,?\s?)?(?<param_def4>\s?(?<optional_flag4>\?)?(?<param_type4>[a-z]{3,8})?\s?(?<reference_flag4>\&)?(?<param_name4>\$[\w\-]{1,20})\s?(?<default_value4>\=\s?[\w\-\']{1,128})?\s?\,?\s?)?(?<param_def5>\s?(?<optional_flag5>\?)?(?<param_type5>[a-z]{3,8})?\s?(?<reference_flag5>\&)?(?<param_name5>\$[\w\-]{1,20})\s?(?<default_value5>\=\s?[\w\-\']{1,128})?\s?\,?\s?)?)?\)?\:?\s?(?<return_type>[\w\-]{2,25})?)/';
    if (preg_match_all($regstr, $apistr, $matches, PREG_SET_ORDER) !== false) {
    
      foreach($matches as $match) {
        
        $method1=[];
      
        if ($match["visibility"] === "public" || $env[$eni]['namespace'] === "-") {
          //var_dump_ifdebug(true, $match);
                
          if ($match["param_defs"]!="") {    
            
            $method1['name'] = $match["name"];
            
            echo_ifdebug(true, "debug: <b>".$match["name"]."(</b>");
            $method1['doc'] = $match["name"]."(";
            
            for($i=1;$i<=5;$i++) {
              if (!empty($match["param_name".$i])) {
                
                $param1 = [];
                $param1['name'] = $match["param_name".$i];
                $param1['type'] = "variant"; 
                $param1['optional'] = false;
                
                if ($i > 1) {
                  echo_ifdebug(true, ",&nbsp;");
                  $method1['doc'].=", ";
                }
                echo_ifdebug(true, $match["param_name".$i]." (");
                $method1['doc'].=$match["param_name".$i]." (";
                if (empty($match["param_type".$i])) {
                  echo_ifdebug(true, "variant");
                  $method1['doc'].="variant";
                } else {
                  $param1['type'] = $match["param_type".$i];
                  
                  echo_ifdebug(true, $match["param_type".$i]);
                  $method1['doc'].=$match["param_type".$i];
                }  
                if ($match["optional_flag".$i] === "?") {
                  $param1['optional'] = true;
                  
                  echo_ifdebug(true, ", optional)");
                  $method1['doc'].=", optional)";
                          
                } else {
                  echo_ifdebug(true, ")");
                  $method1['doc'].=")";
                }  
                
                $method1['params'][] = $param1;  
                
              } else {
                continue;
              }  
            }
            
            if (!isset($match["return_type"])) {
              $method1['return_type'] = "variant";
            } else {
              $method1['return_type'] = $match["return_type"];
            }
            
            $method1['doc'].="):".$method1['return_type'];
            
            $method1['namespace'] = $env[$eni]['namespace'];
            $method1['classname'] = $env[$eni]['classname'];
            
            $methods[ltrim($match["name"],'&')] = $method1;
            
            echo_ifdebug(true, "<b>):".$method1['return_type']."</b><br>");
            
            
          } else {
            
            $method1['name'] = $match["name"];
            $param1 = [];
            $method1['params'] = $param1;

            if (!isset($match["return_type"])) {
              $method1['return_type'] = "variant";
            } else {
              $method1['return_type'] = $match["return_type"];
            }
            
            $method1['doc'] = $match["name"]."():".$method1['return_type'];

            $method1['namespace'] = $env[$eni]['namespace'];
            $method1['classname'] = $env[$eni]['classname'];
            
            $methods[ltrim($match["name"],'&')] = $method1;
                        
            echo_ifdebug(true, "debug: <b>".$match["name"]."():".$method1['return_type']."</b>"."<br>");
            
          }
        }
      }
      
      //$methods[] = $method1;
      
      //var_dump_ifdebug(true, $methods);
      
      // LOADING METHODS
      //var_dump_ifdebug(true, $matches);
      //exit(-1);
      
    }
    $eni++;
  }
} 

//exit(-1);

if (empty($methods)) {
  $methods = [];
}

// Caching the array just loaded
$cache->setJ($cacheKey, $methods, 0, CACHE_EXPIRE);


// PARAMETERS VALIDATION

$url = trim(substr(filter_input(INPUT_GET, "url", FILTER_SANITIZE_STRING), 0, 300), "/");

/*
switch ($url) {
  case "action":
    $scriptPath = APP_AJAX_PATH;
    define("SCRIPT_NAME", "action");
    define("SCRIPT_FILENAME", "action.php");     
    break;
  case "method":
    define("SCRIPT_NAME", "mymethod");
    define("SCRIPT_FILENAME", "mymethod.php");   
    break;
  default:
    $scriptPath = APP_ERROR_PATH;
    define("SCRIPT_NAME", "err-404");
    define("SCRIPT_FILENAME", "err-404.php");  
}
*/

//print_r($methods);
echo_ifdebug(true, "<br>");

if (isset($methods[$url])) {

  $userMethod = $url;
  
  if ($methods[$url]['namespace']==="-" || $methods[$url]['classname'] ==="-") {
    $cmd = 'return '.$url.'('; 
  } else {
    $cmd = 'return '.$methods[$url]['namespace'].'\\'.$methods[$url]['classname'].'::'.$url.'('; 
  }
  
  //print_r($methods[$url]["params"]);
  
  $i=0;
  $query_string = filter_input(INPUT_SERVER, "QUERY_STRING");
  //echo($query_string);
  //echo(strlen($query_string). ">" . (strlen($url)+5));
  if (strlen($query_string) > (strlen($url)+5)) {
  
    foreach($methods[$url]["params"] as $param) {
      $userParams[$i] = filter_input(INPUT_GET, $param['name'], FILTER_SANITIZE_STRING);
      //print_r($userParams[$i]);
      if ($param['type']==="string" && !empty($userParams[$i])) {
        $cmd .= "'$userParams[$i]',";
      } else if ($param['type']==="array") {

        if (is_json($userParams[$i])) {
          // JSON
          $cmd .= jsontolist($userParams[$i]).",";
        } else if((left($userParams[$i],1)==="[" || left($userParams[$i],5)==="array") && is_listformat($userParams[$i])) {
          // LIST OR ARRAY
          $cmd .= $val.",";
        } else {  
          // VALUE => ARRAY
          if (is_numeric($userParams[$i])) {
            $val = $userParams[$i];
          } else {
            $val = "'".$userParams[$i]."'";
          }  
          $val = "[".$val."]";
          $cmd .= $val.",";
        }  

      } else {
        $cmd .= "$userParams[$i],";
      }  
      $i++;
    }
  }
    
  $cmd=rtrim($cmd,",");
  $cmd .= ");";
  //echo("cmd=$cmd");
  
  set_exception_handler('eval_ex_handler');
  $ret = eval($cmd);
  if ($methods[$url]["return_type"]==="bool") {
    echo(($ret?"true":"false"));
  } else {  
    echo($ret);
  }  

} else if ($url === "XMLDOC") {  
  
  if (!DEBUG) {

    header("Content-Type: text/xml");
 
    //print_r($env);
    
    echo('<?xml version="1.0" encoding="utf-8"?>');
    echo('<API>');
    foreach($env as $e) {
      $curnamespace = $e['namespace'];    
      $curclassname = $e['classname'];

      foreach($methods as $m) {
        //echo($m['namespace']."===".$curnamespace."<br>");
        //echo($m['classname']."===".$curclassname."<br>");
        if (($m['namespace'] === $curnamespace) && ($m['classname'] === $curclassname))  {
          echo("<METHOD>");
          echo('<NAMESPACE>'.$m['namespace'].'</NAMESPACE>'); 
          echo('<CLASSNAME>'.$m['classname'].'</CLASSNAME>'); 
          echo('<NAME>'.$m['name'].'</NAME>');
          
          $pi=1;
          foreach($m['params'] as $p) {          
            echo("<PARAM$pi type='".$p['type']."' optional='".($p['optional']==1?"true":"false")."'>".$p['name']."</PARAM$pi>"); 
            $pi++;
          }  
                    
          echo('<RETURN_TYPE>'.$m['return_type'].'</RETURN_TYPE>'); 
          echo('<HEADER>'.$m['doc'].'</HEADER>'); 
          echo("</METHOD>");
        }
      }
    }
    echo('</API>');
  }  
    
} else {
  $scriptPath = APP_ERROR_PATH;
  define("SCRIPT_NAME", "err-404");
  define("SCRIPT_FILENAME", "err-404.php");  

  if (SCRIPT_NAME==="err-404") {
    header("HTTP/1.1 404 Not Found");
  }  

  require $scriptPath . "/" . SCRIPT_FILENAME;
}