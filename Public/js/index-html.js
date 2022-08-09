
/*
 * Copyright (c) 2016, 2024, 5 Mode
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither 5 Mode nor the names of its contributors 
 *     may be used to endorse or promote products derived from this software 
 *     without specific prior written permission.
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
 * https://opensource.org/licenses/BSD-3-Clause
 * 
 */

var appMenuVisible=false;
var onAppMenu = false;

$("div#butParent").click(function() {
  window.open("http://5mode.com", "_self");
});

function popupMenu() {
  if (!appMenuVisible) {
    $(".appMenu").show();
    $(".appMenu").css("z-index", "99999");
    $(".content5").css("z-index", "99998");
    $(".content5").css("opacity", "0.3");
  } else {
    $(".appMenu").hide();
    $(".appMenu").css("z-index", "99992");
    $(".content5").css("z-index", "99999");
    $(".content5").css("opacity", "1.0");
  }
  appMenuVisible=!appMenuVisible;
} 

function hideMenu() {
  $(".appMenu").hide();
  appMenuVisible=false;
  $(".content5").css("opacity", "1.0");
} 

$("#appMenuIco").on("mouseover", function() {
    onAppMenu = true;
});

$("#appMenuIco").on("mouseout", function() {
    onAppMenu = false;
});

$(".appMenu").on("mouseover", function() {
    onAppMenu = true;
});

$(".appMenu").on("mouseout", function() {
    onAppMenu = false;
});

$("body").on("click", function() {
  if (!onAppMenu) {
    hideMenu();
  }
});

function setFooterPos() {
  if (document.getElementById("footerCont")) {
    tollerance = 16;
    $("#footerCont").css("top", parseInt( window.innerHeight - $("#footerCont").height() - tollerance ) + "px");
    $("#footer").css("top", parseInt( window.innerHeight - $("#footer").height() - tollerance ) + "px");
  }
}

window.addEventListener("load", function() {
  setTimeout("setFooterPos()", 1000);
  
  $("div.appMenu").load("https://appmenu.5mode.com/?v="+ rnd(50000, 99999));
}, true);

window.addEventListener("resize", function() {
  setTimeout("setFooterPos()", 1000);
  
  hideMenu();
}, true);


