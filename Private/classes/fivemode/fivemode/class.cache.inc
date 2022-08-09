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
 * class.cache.inc
 * 
 * Cached class.
 *
 * @author Daniele Bonini <my25mb@aol.com>
 * @copyrights (c) 2016, 2024, 5 Mode
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace fivemode\fivemode;

/**
 * Cache
 *
 * Cache class
 *
 * @package  Cache
 * @author   Daniele Bonini <my25mb@aol.com>
 * @version  2.0
 * @access   public
 */
final class Cache extends \Memcached
{
  /**
   * The static instance of Cache
   *  
   * @access private
   * @var Cache
   */
  private static $_instance = null;

  /**
   * Get the static instance of Cache 
   * 
   * @return Cache
   */
  public static function &getInstance(): Cache
  {  
    if(!isset(self::$_instance)){
      self::$_instance = new Cache();
      self::$_instance->addServer(CACHE_HOST, CACHE_PORT);
    }  
    return self::$_instance;  
  }

  /**
   * Get the service status
   * 
   * @return bool
   */
  public static function getStatus(): bool
  {  
    return true;
  }
  
  /**
   * Check if the static instance is set
   * 
   * @return bool
   */
  public static function issetInstance(): bool
  {
    return isset(self::$_instance);
  }
  
  /**
   * Unset the static instance
   * 
   * @return void
   */
  public static function unsetInstance(): void
  {
    if (self::$_instance) {
      self::$_instance->quit();
      self::$_instance = null;
    }  
  }

  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
    parent::__construct();
  }
  
  /**
   * Retrieve item from the cache server
   * 
   * @param string $key the key to fetch
   * @param int $flags the flags
   * @return mixed the value stored in cache or false
   */
  public function getObj(string $key, ?int $flags = null) 
  {
    if (!isset($flags)) {
      $ret = $this->get(CACHE_APP_PREFIX . $key);
    } else {
      $ret = $this->get(CACHE_APP_PREFIX . $key, null, $flags);
    }  
    if ($this->getResultCode() == \Memcached::RES_NOTFOUND) {
      return false;
    } else {
      return $ret;
    }
  }
  
  /**
   * Store data in the cache server
   * 
   * @param string $key the key to associated with the item.
   * @param mixed $var the object to store
   * @param int $flags the flags
   * @param int $expire expiration time, in seconds
   * @return bool true on success or false on failure 
   */
  public function setObj(string $key, &$var, ?int $flags = null, ?int $expire = null): bool 
  {
    // cache insert
    if (!isset($expire)) {
      return $this->set(CACHE_APP_PREFIX . $key, $var);
    }
    return $this->set(CACHE_APP_PREFIX . $key, $var, $expire);
  }
  
  /**
   * Retrieve item from the cache server (decoded by json_decode)
   * 
   * @param string $key the key to fetch
   * @param int $flags the flags
   * @return mixed the value stored in cache or false
   */
  public function getJ(string $key, ?int $flags = null) 
  {
    if (!isset($flags)) {
      $ret = json_decode($this->get(CACHE_APP_PREFIX . $key), true);
    } else {
      $ret = json_decode($this->get(CACHE_APP_PREFIX . $key, null, $flags), true);
    }  
    if ($this->getResultCode() == \Memcached::RES_NOTFOUND) {
      return false;
    } else {
      return $ret;
    }

  }
  
  /**
   * Store data in the cache server (encoded by json_encode)
   * 
   * @param string $key the key to associated with the item.
   * @param mixed $var the value to store
   * @param int $flags the flags
   * @param int $expire expiration time, in seconds
   * @return bool true on success or false on failure 
   */
  public function setJ(string $key, &$var, ?int $flags = null, ?int $expire = null): bool
  {
    // cache insert
    if (!isset($expire)) {
      return $this->set(CACHE_APP_PREFIX . $key, json_encode($var));
    }
    return $this->set(CACHE_APP_PREFIX . $key, json_encode($var), $expire);
  }
  
  /**
   * Test the validity of the "global" cache expiration time
   * 
   * @param string $testText the text used to generate the key for the test
   * 
   * @return bool true if the caching expiration time is not gone
   */
   public function testLastCached($testText) {
     return json_decode($this->get(md5($testText)), true);
   }  
}
