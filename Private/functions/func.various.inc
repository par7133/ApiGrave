<?php

/**
 * Copyright (c) 2016, 2019, Open Gallery
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither Open Gallery nor the names of its contributors 
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
 * func.various.inc
 * 
 * Functions of various kind.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2019, Open Gallery  
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

/**
 * Replacement for echo with debug checking
 * 
 * @param boolean $debug_var a debug value, if true the echo will be executed 
 * @param list $args a variable argument list
 * @return void
 */
function echo_ifdebug($debug_var, ...$args) {
  if (!DEBUG || !$debug_var) {
    return;
  }
  foreach($args as $arg) {
    echo $arg;
  }
}

/**
 * Get an integer result for a division
 * 
 * @param mixed $a first operand
 * @param mixed $b second operand
 * @return int the integer result
 */
function intdiv_1($a, $b) {
  return ($a - $a % $b) / $b;
}

/**
 * Check if the number is odd
 * 
 * @param mixed $a first operand
 * @return bool if the number is odd, true/false
 */
function is_odd($a) {
  return ($a % 2) > 0;
}

/**
 * Check if the number is pair
 * 
 * @param mixed $a first operand
 * @return bool if the number is pair, true/false
 */
function is_pair($a) {
  return ($a % 2) === 0;
}

/**
 * Check if a variable is set with a default return
 * 
 * @param mixed $var the variable to check
 * @param mixed $default the default value
 * @return mixed the return value
 */
function isset1(&$var, $default=false) {
  if (isset($var)) {
    return $var;
  } else {
    return $default;
  }
}

/**
 * Replacement for var_dump with debug checking
 * 
 * @param boolean $debug_var a debug value, if true the var_dump will be executed 
 * @param list $args a variable argument list
 * @return void
 */
function var_dump_ifdebug($debug_var, ...$args) {
  if (!DEBUG || !$debug_var) {
    return;
  }
  foreach($args as $arg) {
    var_dump($arg);
  }
}
