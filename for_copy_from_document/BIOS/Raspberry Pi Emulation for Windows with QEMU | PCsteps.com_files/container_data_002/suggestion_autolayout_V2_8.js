(function(){var h,k=this,l=function(a){return void 0!==a},m=function(a,b,c){a=a.split(".");c=c||k;a[0]in c||!c.execScript||c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)!a.length&&l(b)?c[d]=b:c=c[d]?c[d]:c[d]={}},aa=function(){},ba=function(a){var b=typeof a;if("object"==b)if(a){if(a instanceof Array)return"array";if(a instanceof Object)return b;var c=Object.prototype.toString.call(a);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof a.length&&"undefined"!=typeof a.splice&&
"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof a.call&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("call"))return"function"}else return"null";else if("function"==b&&"undefined"==typeof a.call)return"object";return b},n=function(a){return"array"==ba(a)},ca=function(a){var b=ba(a);return"array"==b||"object"==b&&"number"==typeof a.length},p=function(a){return"string"==typeof a},da=function(a){return"function"==
ba(a)},ea=function(a){var b=typeof a;return"object"==b&&null!=a||"function"==b},fa=function(a,b,c){return a.call.apply(a.bind,arguments)},ga=function(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var c=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(c,d);return a.apply(b,c)}}return function(){return a.apply(b,arguments)}},q=function(a,b,c){q=Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?
fa:ga;return q.apply(null,arguments)},ha=function(a,b){var c=Array.prototype.slice.call(arguments,1);return function(){var b=c.slice();b.push.apply(b,arguments);return a.apply(this,b)}},t=Date.now||function(){return+new Date},u=function(a,b){function c(){}c.prototype=b.prototype;a.H=b.prototype;a.prototype=new c;a.Ia=function(a,c,f){for(var d=Array(arguments.length-2),e=2;e<arguments.length;e++)d[e-2]=arguments[e];return b.prototype[c].apply(a,d)}};var ia=String.prototype.trim?function(a){return a.trim()}:function(a){return a.replace(/^[\s\xa0]+|[\s\xa0]+$/g,"")},ra=function(a){if(!ka.test(a))return a;-1!=a.indexOf("&")&&(a=a.replace(la,"&amp;"));-1!=a.indexOf("<")&&(a=a.replace(ma,"&lt;"));-1!=a.indexOf(">")&&(a=a.replace(na,"&gt;"));-1!=a.indexOf('"')&&(a=a.replace(oa,"&quot;"));-1!=a.indexOf("'")&&(a=a.replace(pa,"&#39;"));-1!=a.indexOf("\x00")&&(a=a.replace(qa,"&#0;"));return a},la=/&/g,ma=/</g,na=/>/g,oa=/"/g,pa=/'/g,qa=/\x00/g,ka=/[\x00&<>"']/,
v=function(a,b){return-1!=a.indexOf(b)},ta=function(a,b){var c=0;a=ia(String(a)).split(".");b=ia(String(b)).split(".");for(var d=Math.max(a.length,b.length),e=0;0==c&&e<d;e++){var f=a[e]||"",g=b[e]||"";do{f=/(\d*)(\D*)(.*)/.exec(f)||["","","",""];g=/(\d*)(\D*)(.*)/.exec(g)||["","","",""];if(0==f[0].length&&0==g[0].length)break;c=sa(0==f[1].length?0:parseInt(f[1],10),0==g[1].length?0:parseInt(g[1],10))||sa(0==f[2].length,0==g[2].length)||sa(f[2],g[2]);f=f[3];g=g[3]}while(0==c)}return c},sa=function(a,
b){return a<b?-1:a>b?1:0},ua=function(a){return String(a).replace(/\-([a-z])/g,function(a,c){return c.toUpperCase()})},va=function(a){var b=p(void 0)?"undefined".replace(/([-()\[\]{}+?*.$\^|,:#<!\\])/g,"\\$1").replace(/\x08/g,"\\x08"):"\\s";return a.replace(new RegExp("(^"+(b?"|["+b+"]+":"")+")([a-z])","g"),function(a,b,e){return b+e.toUpperCase()})};var wa=Array.prototype.indexOf?function(a,b,c){return Array.prototype.indexOf.call(a,b,c)}:function(a,b,c){c=null==c?0:0>c?Math.max(0,a.length+c):c;if(p(a))return p(b)&&1==b.length?a.indexOf(b,c):-1;for(;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1},xa=Array.prototype.forEach?function(a,b,c){Array.prototype.forEach.call(a,b,c)}:function(a,b,c){for(var d=a.length,e=p(a)?a.split(""):a,f=0;f<d;f++)f in e&&b.call(c,e[f],f,a)},ya=function(a){return Array.prototype.concat.apply(Array.prototype,
arguments)},za=function(a){var b=a.length;if(0<b){for(var c=Array(b),d=0;d<b;d++)c[d]=a[d];return c}return[]};var Aa=function(a,b,c){for(var d in a)b.call(c,a[d],d,a)},Ba="constructor hasOwnProperty isPrototypeOf propertyIsEnumerable toLocaleString toString valueOf".split(" "),Ca=function(a,b){for(var c,d,e=1;e<arguments.length;e++){d=arguments[e];for(c in d)a[c]=d[c];for(var f=0;f<Ba.length;f++)c=Ba[f],Object.prototype.hasOwnProperty.call(d,c)&&(a[c]=d[c])}};var w;a:{var Da=k.navigator;if(Da){var Ea=Da.userAgent;if(Ea){w=Ea;break a}}w=""};var Fa=function(a){Fa[" "](a);return a};Fa[" "]=aa;var Ha=function(a,b){var c=Ga;return Object.prototype.hasOwnProperty.call(c,a)?c[a]:c[a]=b(a)};var Ia=v(w,"Opera"),x=v(w,"Trident")||v(w,"MSIE"),Ja=v(w,"Edge"),y=v(w,"Gecko")&&!(v(w.toLowerCase(),"webkit")&&!v(w,"Edge"))&&!(v(w,"Trident")||v(w,"MSIE"))&&!v(w,"Edge"),A=v(w.toLowerCase(),"webkit")&&!v(w,"Edge"),Ka=function(){var a=k.document;return a?a.documentMode:void 0},La;
a:{var Ma="",Na=function(){var a=w;if(y)return/rv\:([^\);]+)(\)|;)/.exec(a);if(Ja)return/Edge\/([\d\.]+)/.exec(a);if(x)return/\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/.exec(a);if(A)return/WebKit\/(\S+)/.exec(a);if(Ia)return/(?:Version)[ \/]?(\S+)/.exec(a)}();Na&&(Ma=Na?Na[1]:"");if(x){var Oa=Ka();if(null!=Oa&&Oa>parseFloat(Ma)){La=String(Oa);break a}}La=Ma}var Pa=La,Ga={},B=function(a){return Ha(a,function(){return 0<=ta(Pa,a)})},Qa;var Ra=k.document;
Qa=Ra&&x?Ka()||("CSS1Compat"==Ra.compatMode?parseInt(Pa,10):5):void 0;var Sa=!x||9<=Number(Qa);!y&&!x||x&&9<=Number(Qa)||y&&B("1.9.1");x&&B("9");var C=function(a){var b=document;return p(a)?b.getElementById(a):a},Ua=function(a,b){Aa(b,function(b,d){"style"==d?a.style.cssText=b:"class"==d?a.className=b:"for"==d?a.htmlFor=b:Ta.hasOwnProperty(d)?a.setAttribute(Ta[d],b):0==d.lastIndexOf("aria-",0)||0==d.lastIndexOf("data-",0)?a.setAttribute(d,b):a[d]=b})},Ta={cellpadding:"cellPadding",cellspacing:"cellSpacing",colspan:"colSpan",frameborder:"frameBorder",height:"height",maxlength:"maxLength",nonce:"nonce",role:"role",rowspan:"rowSpan",type:"type",
usemap:"useMap",valign:"vAlign",width:"width"},Wa=function(a,b,c){var d=arguments,e=document,f=String(d[0]),g=d[1];if(!Sa&&g&&(g.name||g.type)){f=["<",f];g.name&&f.push(' name="',ra(g.name),'"');if(g.type){f.push(' type="',ra(g.type),'"');var r={};Ca(r,g);delete r.type;g=r}f.push(">");f=f.join("")}f=e.createElement(f);g&&(p(g)?f.className=g:n(g)?f.className=g.join(" "):Ua(f,g));2<d.length&&Va(e,f,d);return f},Va=function(a,b,c){function d(c){c&&b.appendChild(p(c)?a.createTextNode(c):c)}for(var e=
2;e<c.length;e++){var f=c[e];!ca(f)||ea(f)&&0<f.nodeType?d(f):xa(Xa(f)?za(f):f,d)}},Ya=function(a){a&&a.parentNode&&a.parentNode.removeChild(a)},Xa=function(a){if(a&&"number"==typeof a.length){if(ea(a))return"function"==typeof a.item||"string"==typeof a.item;if(da(a))return"function"==typeof a.item}return!1};var Za=function(a,b){this.ua=a;this.oa=b};Za.prototype.toString=function(){return this.ua+"x"+this.oa};var D=function(a,b){return a.google_template_data.adData[0][b]},$a=function(a){a=D(a,"siriusFlagUnclickableBorderSize");if(p(a))if("["==a.charAt(0)&&"]"==a.charAt(a.length-1)){for(var b=a.slice(1,-1).split(","),c=[],d=0;d<b.length;++d)c.push(isNaN(b[d])?0:parseInt(b[d],10));if(4==c.length)return c}else return a=isNaN(a)?0:parseInt(a,10),[a,a,a,a];if("number"==typeof a)return a=parseInt(a,10),[a,a,a,a];if(n(a)){c=[];for(d=0;d<a.length;++d)"number"==typeof a[d]&&c.push(parseInt(a[d],10));if(4==c.length)return c}return[0,
0,0,0]},ab=function(a){a=D(a,"siriusFlagCloseButtonClickProtectorSize");return isNaN(a)?100:parseInt(a,10)},bb=function(a){return"true"==D(a,"siriusFlagEnableNewBorderProtection")};var cb=function(a,b){a=a.google_template_data.rendering_settings;if("object"!=ba(a))return null;b=a[b];return p(b)?b:null},db=function(a){var b=cb(a,"format");if(!p(b))if(a=a.google_template_data.adData[0].format,p(a)||null==a)b=a;else throw Error("Gets non string value from: format");return b},eb=function(a){return"true"==cb(a,"bgSignal")};var fb=!x||9<=Number(Qa),gb=x&&!B("9");!A||B("528");y&&B("1.9b")||x&&B("8")||Ia&&B("9.5")||A&&B("528");y&&!B("8")||x&&B("9");var E=function(){this.K=this.K;this.B=this.B};E.prototype.K=!1;E.prototype.na=function(){this.K||(this.K=!0,this.s())};E.prototype.s=function(){if(this.B)for(;this.B.length;)this.B.shift()()};var ib=function(a){a&&"function"==typeof a.na&&a.na()};var F=function(a,b){this.type=a;this.currentTarget=this.target=b;this.defaultPrevented=this.C=!1;this.ta=!0};F.prototype.stopPropagation=function(){this.C=!0};F.prototype.preventDefault=function(){this.defaultPrevented=!0;this.ta=!1};var G=function(a,b){F.call(this,a?a.type:"");this.relatedTarget=this.currentTarget=this.target=null;this.charCode=this.keyCode=this.button=this.screenY=this.screenX=this.clientY=this.clientX=this.offsetY=this.offsetX=0;this.metaKey=this.shiftKey=this.altKey=this.ctrlKey=!1;this.M=this.state=null;if(a){var c=this.type=a.type,d=a.changedTouches?a.changedTouches[0]:null;this.target=a.target||a.srcElement;this.currentTarget=b;if(b=a.relatedTarget){if(y){var e;a:{try{Fa(b.nodeName);e=!0;break a}catch(f){}e=
!1}e||(b=null)}}else"mouseover"==c?b=a.fromElement:"mouseout"==c&&(b=a.toElement);this.relatedTarget=b;null===d?(this.offsetX=A||void 0!==a.offsetX?a.offsetX:a.layerX,this.offsetY=A||void 0!==a.offsetY?a.offsetY:a.layerY,this.clientX=void 0!==a.clientX?a.clientX:a.pageX,this.clientY=void 0!==a.clientY?a.clientY:a.pageY,this.screenX=a.screenX||0,this.screenY=a.screenY||0):(this.clientX=void 0!==d.clientX?d.clientX:d.pageX,this.clientY=void 0!==d.clientY?d.clientY:d.pageY,this.screenX=d.screenX||0,
this.screenY=d.screenY||0);this.button=a.button;this.keyCode=a.keyCode||0;this.charCode=a.charCode||("keypress"==c?a.keyCode:0);this.ctrlKey=a.ctrlKey;this.altKey=a.altKey;this.shiftKey=a.shiftKey;this.metaKey=a.metaKey;this.state=a.state;this.M=a;a.defaultPrevented&&this.preventDefault()}};u(G,F);G.prototype.stopPropagation=function(){G.H.stopPropagation.call(this);this.M.stopPropagation?this.M.stopPropagation():this.M.cancelBubble=!0};
G.prototype.preventDefault=function(){G.H.preventDefault.call(this);var a=this.M;if(a.preventDefault)a.preventDefault();else if(a.returnValue=!1,gb)try{if(a.ctrlKey||112<=a.keyCode&&123>=a.keyCode)a.keyCode=-1}catch(b){}};var jb="closure_listenable_"+(1E6*Math.random()|0),H=function(a){return!(!a||!a[jb])},kb=0;var lb=function(a,b,c,d,e){this.listener=a;this.Y=null;this.src=b;this.type=c;this.capture=!!d;this.U=e;this.key=++kb;this.F=this.S=!1},nb=function(a){a.F=!0;a.listener=null;a.Y=null;a.src=null;a.U=null};var I=function(a){this.src=a;this.g={};this.R=0};I.prototype.add=function(a,b,c,d,e){var f=a.toString();a=this.g[f];a||(a=this.g[f]=[],this.R++);var g=ob(a,b,d,e);-1<g?(b=a[g],c||(b.S=!1)):(b=new lb(b,this.src,f,!!d,e),b.S=c,a.push(b));return b};I.prototype.remove=function(a,b,c,d){a=a.toString();if(!(a in this.g))return!1;var e=this.g[a];b=ob(e,b,c,d);return-1<b?(nb(e[b]),Array.prototype.splice.call(e,b,1),0==e.length&&(delete this.g[a],this.R--),!0):!1};
var pb=function(a,b){var c=b.type;if(c in a.g){var d=a.g[c],e=wa(d,b),f;(f=0<=e)&&Array.prototype.splice.call(d,e,1);f&&(nb(b),0==a.g[c].length&&(delete a.g[c],a.R--))}};I.prototype.ha=function(a){a=a&&a.toString();var b=0,c;for(c in this.g)if(!a||c==a){for(var d=this.g[c],e=0;e<d.length;e++)++b,nb(d[e]);delete this.g[c];this.R--}return b};I.prototype.O=function(a,b,c,d){a=this.g[a.toString()];var e=-1;a&&(e=ob(a,b,c,d));return-1<e?a[e]:null};
var ob=function(a,b,c,d){for(var e=0;e<a.length;++e){var f=a[e];if(!f.F&&f.listener==b&&f.capture==!!c&&f.U==d)return e}return-1};var qb="closure_lm_"+(1E6*Math.random()|0),rb={},sb=0,J=function(a,b,c,d,e){if(n(b)){for(var f=0;f<b.length;f++)J(a,b[f],c,d,e);return null}c=tb(c);return H(a)?a.listen(b,c,d,e):ub(a,b,c,!1,d,e)},ub=function(a,b,c,d,e,f){if(!b)throw Error("Invalid event type");var g=!!e,r=K(a);r||(a[qb]=r=new I(a));c=r.add(b,c,d,e,f);if(c.Y)return c;d=vb();c.Y=d;d.src=a;d.listener=c;if(a.addEventListener)a.addEventListener(b.toString(),d,g);else if(a.attachEvent)a.attachEvent(wb(b.toString()),d);else throw Error("addEventListener and attachEvent are unavailable.");
sb++;return c},vb=function(){var a=xb,b=fb?function(c){return a.call(b.src,b.listener,c)}:function(c){c=a.call(b.src,b.listener,c);if(!c)return c};return b},L=function(a,b,c,d,e){if(n(b)){for(var f=0;f<b.length;f++)L(a,b[f],c,d,e);return null}c=tb(c);return H(a)?a.pa(b,c,d,e):ub(a,b,c,!0,d,e)},yb=function(a,b,c,d,e){if(n(b))for(var f=0;f<b.length;f++)yb(a,b[f],c,d,e);else c=tb(c),H(a)?a.unlisten(b,c,d,e):a&&(a=K(a))&&(b=a.O(b,c,!!d,e))&&zb(b)},zb=function(a){if("number"!=typeof a&&a&&!a.F){var b=
a.src;if(H(b))pb(b.v,a);else{var c=a.type,d=a.Y;b.removeEventListener?b.removeEventListener(c,d,a.capture):b.detachEvent&&b.detachEvent(wb(c),d);sb--;(c=K(b))?(pb(c,a),0==c.R&&(c.src=null,b[qb]=null)):nb(a)}}},wb=function(a){return a in rb?rb[a]:rb[a]="on"+a},Bb=function(a,b,c,d){var e=!0;if(a=K(a))if(b=a.g[b.toString()])for(b=b.concat(),a=0;a<b.length;a++){var f=b[a];f&&f.capture==c&&!f.F&&(f=Ab(f,d),e=e&&!1!==f)}return e},Ab=function(a,b){var c=a.listener,d=a.U||a.src;a.S&&zb(a);return c.call(d,
b)},xb=function(a,b){if(a.F)return!0;if(!fb){if(!b)a:{b=["window","event"];for(var c=k,d;d=b.shift();)if(null!=c[d])c=c[d];else{b=null;break a}b=c}d=b;b=new G(d,this);c=!0;if(!(0>d.keyCode||void 0!=d.returnValue)){a:{var e=!1;if(0==d.keyCode)try{d.keyCode=-1;break a}catch(g){e=!0}if(e||void 0==d.returnValue)d.returnValue=!0}d=[];for(e=b.currentTarget;e;e=e.parentNode)d.push(e);a=a.type;for(e=d.length-1;!b.C&&0<=e;e--){b.currentTarget=d[e];var f=Bb(d[e],a,!0,b),c=c&&f}for(e=0;!b.C&&e<d.length;e++)b.currentTarget=
d[e],f=Bb(d[e],a,!1,b),c=c&&f}return c}return Ab(a,new G(b,this))},K=function(a){a=a[qb];return a instanceof I?a:null},Cb="__closure_events_fn_"+(1E9*Math.random()>>>0),tb=function(a){if(da(a))return a;a[Cb]||(a[Cb]=function(b){return a.handleEvent(b)});return a[Cb]};var M=function(a,b){if(p(b))(b=Db(a,b))&&(a.style[b]=void 0);else for(var c in b){var d=a,e=b[c],f=Db(d,c);f&&(d.style[f]=e)}},Eb={},Db=function(a,b){var c=Eb[b];if(!c){var d=ua(b),c=d;void 0===a.style[d]&&(d=(A?"Webkit":y?"Moz":x?"ms":Ia?"O":null)+va(d),void 0!==a.style[d]&&(c=d));Eb[b]=c}return c},Fb=function(a,b){var c=9==a.nodeType?a:a.ownerDocument||a.document;return c.defaultView&&c.defaultView.getComputedStyle&&(a=c.defaultView.getComputedStyle(a,null))?a[b]||a.getPropertyValue(b)||"":""};var Gb={background:"rgba(0, 0, 0, 0)",zIndex:1E3,cursor:"pointer",position:"absolute",left:"0",top:"0",width:"100%",height:"100%"},Hb=function(a,b,c){var d=a.id+"-clickOverlay";Ya(C(d));var e=Wa("A");e.id=d;e.href=b;e.target=c;M(e,Gb);a.appendChild(e);return e},Kb=function(a,b){if(!bb(b)){var c=$a(b);if(0<c[0]){var d=Ib(a,"-ucborder0");M(d,{width:c[0]+"px",height:"100%"})}0<c[1]&&(d=Ib(a,"-ucborder1"),M(d,{width:"100%",height:c[1]+"px"}));0<c[2]&&(d=Ib(a,"-ucborder2"),M(d,{width:c[2]+"px",height:"100%",
right:"0px"}));0<c[3]&&(a=Ib(a,"-ucborder3"),M(a,{width:"100%",height:c[3]+"px",bottom:"0px"}))}Jb(b)},Jb=function(a){Ya(C("cbprotection"));if(!(bb(a)||"interstitial_mb"!=db(a)||(a=ab(a),0>=a))){var b=document.createElement("DIV");b.id="cbprotection";b.style.position="fixed";b.style.top="0";b.style.left="0";b.style.width=a+"px";b.style.height=a+"px";b.style.zIndex=2E3;J(b,"click",function(a){a.stopPropagation()});document.body.appendChild(b)}},Ib=function(a,b){b=a.id+b;Ya(C(b));var c=Wa("DIV");c.style.position=
"absolute";c.style.zIndex=2E3;c.id=b;a.appendChild(c);return c};var Lb=function(a,b){this.qa=a;this.ra=b||{}},Mb=function(a,b){F.call(this,a.qa,b);this.Ea=a.ra||{}};u(Mb,F);var Nb="StopIteration"in k?k.StopIteration:{message:"StopIteration",stack:""},Ob=function(){};Ob.prototype.next=function(){throw Nb;};Ob.prototype.va=function(){return this};var N=function(a,b){this.l={};this.b=[];this.aa=this.f=0;var c=arguments.length;if(1<c){if(c%2)throw Error("Uneven number of arguments");for(var d=0;d<c;d+=2)this.set(arguments[d],arguments[d+1])}else a&&this.addAll(a)};N.prototype.D=function(){Pb(this);for(var a=[],b=0;b<this.b.length;b++)a.push(this.l[this.b[b]]);return a};N.prototype.N=function(){Pb(this);return this.b.concat()};N.prototype.J=function(a){return O(this.l,a)};
N.prototype.remove=function(a){return O(this.l,a)?(delete this.l[a],this.f--,this.aa++,this.b.length>2*this.f&&Pb(this),!0):!1};var Pb=function(a){if(a.f!=a.b.length){for(var b=0,c=0;b<a.b.length;){var d=a.b[b];O(a.l,d)&&(a.b[c++]=d);b++}a.b.length=c}if(a.f!=a.b.length){for(var e={},c=b=0;b<a.b.length;)d=a.b[b],O(e,d)||(a.b[c++]=d,e[d]=1),b++;a.b.length=c}};h=N.prototype;h.get=function(a,b){return O(this.l,a)?this.l[a]:b};
h.set=function(a,b){O(this.l,a)||(this.f++,this.b.push(a),this.aa++);this.l[a]=b};h.addAll=function(a){var b;if(a instanceof N)b=a.N(),a=a.D();else{b=[];var c=0,d;for(d in a)b[c++]=d;c=[];d=0;for(var e in a)c[d++]=a[e];a=c}for(e=0;e<b.length;e++)this.set(b[e],a[e])};h.forEach=function(a,b){for(var c=this.N(),d=0;d<c.length;d++){var e=c[d],f=this.get(e);a.call(b,f,e,this)}};h.clone=function(){return new N(this)};
h.va=function(a){Pb(this);var b=0,c=this.aa,d=this,e=new Ob;e.next=function(){if(c!=d.aa)throw Error("The map has changed since the iterator was created");if(b>=d.b.length)throw Nb;var e=d.b[b++];return a?e:d.l[e]};return e};var O=function(a,b){return Object.prototype.hasOwnProperty.call(a,b)};var Qb=/^(?:([^:/?#.]+):)?(?:\/\/(?:([^/?#]*)@)?([^/#?]*?)(?::([0-9]+))?(?=[/#?]|$))?([^?#]+)?(?:\?([^#]*))?(?:#([\s\S]*))?$/,Rb=function(a,b){if(a){a=a.split("&");for(var c=0;c<a.length;c++){var d=a[c].indexOf("="),e,f=null;0<=d?(e=a[c].substring(0,d),f=a[c].substring(d+1)):e=a[c];b(e,f?decodeURIComponent(f.replace(/\+/g," ")):"")}}},Sb=function(a,b,c){if(n(b))for(var d=0;d<b.length;d++)Sb(a,String(b[d]),c);else null!=b&&c.push("&",a,""===b?"":"=",encodeURIComponent(String(b)))};var P=function(a,b){this.L=this.$=this.G="";this.X=null;this.T=this.W="";this.j=this.Ba=!1;var c;a instanceof P?(this.j=l(b)?b:a.j,Tb(this,a.G),c=a.$,Q(this),this.$=c,c=a.L,Q(this),this.L=c,Ub(this,a.X),c=a.W,Q(this),this.W=c,Vb(this,a.m.clone()),a=a.T,Q(this),this.T=a):a&&(c=String(a).match(Qb))?(this.j=!!b,Tb(this,c[1]||"",!0),a=c[2]||"",Q(this),this.$=R(a),a=c[3]||"",Q(this),this.L=R(a,!0),Ub(this,c[4]),a=c[5]||"",Q(this),this.W=R(a,!0),Vb(this,c[6]||"",!0),a=c[7]||"",Q(this),this.T=R(a)):(this.j=
!!b,this.m=new S(null,0,this.j))};P.prototype.toString=function(){var a=[],b=this.G;b&&a.push(Wb(b,Xb,!0),":");var c=this.L;if(c||"file"==b)a.push("//"),(b=this.$)&&a.push(Wb(b,Xb,!0),"@"),a.push(encodeURIComponent(String(c)).replace(/%25([0-9a-fA-F]{2})/g,"%$1")),c=this.X,null!=c&&a.push(":",String(c));if(c=this.W)this.L&&"/"!=c.charAt(0)&&a.push("/"),a.push(Wb(c,"/"==c.charAt(0)?Yb:Zb,!0));(c=this.m.toString())&&a.push("?",c);(c=this.T)&&a.push("#",Wb(c,$b));return a.join("")};
P.prototype.clone=function(){return new P(this)};var Tb=function(a,b,c){Q(a);a.G=c?R(b,!0):b;a.G&&(a.G=a.G.replace(/:$/,""))},Ub=function(a,b){Q(a);if(b){b=Number(b);if(isNaN(b)||0>b)throw Error("Bad port number "+b);a.X=b}else a.X=null},Vb=function(a,b,c){Q(a);b instanceof S?(a.m=b,a.m.ka(a.j)):(c||(b=Wb(b,ac)),a.m=new S(b,0,a.j))},Q=function(a){if(a.Ba)throw Error("Tried to modify a read-only Uri");};P.prototype.ka=function(a){this.j=a;this.m&&this.m.ka(a);return this};
var R=function(a,b){return a?b?decodeURI(a.replace(/%25/g,"%2525")):decodeURIComponent(a):""},Wb=function(a,b,c){return p(a)?(a=encodeURI(a).replace(b,bc),c&&(a=a.replace(/%25([0-9a-fA-F]{2})/g,"%$1")),a):null},bc=function(a){a=a.charCodeAt(0);return"%"+(a>>4&15).toString(16)+(a&15).toString(16)},Xb=/[#\/\?@]/g,Zb=/[\#\?:]/g,Yb=/[\#\?]/g,ac=/[\#\?@]/g,$b=/#/g,S=function(a,b,c){this.f=this.c=null;this.i=a||null;this.j=!!c},T=function(a){a.c||(a.c=new N,a.f=0,a.i&&Rb(a.i,function(b,c){a.add(decodeURIComponent(b.replace(/\+/g,
" ")),c)}))};h=S.prototype;h.add=function(a,b){T(this);this.i=null;a=U(this,a);var c=this.c.get(a);c||this.c.set(a,c=[]);c.push(b);this.f+=1;return this};h.remove=function(a){T(this);a=U(this,a);return this.c.J(a)?(this.i=null,this.f-=this.c.get(a).length,this.c.remove(a)):!1};h.J=function(a){T(this);a=U(this,a);return this.c.J(a)};h.N=function(){T(this);for(var a=this.c.D(),b=this.c.N(),c=[],d=0;d<b.length;d++)for(var e=a[d],f=0;f<e.length;f++)c.push(b[d]);return c};
h.D=function(a){T(this);var b=[];if(p(a))this.J(a)&&(b=ya(b,this.c.get(U(this,a))));else{a=this.c.D();for(var c=0;c<a.length;c++)b=ya(b,a[c])}return b};h.set=function(a,b){T(this);this.i=null;a=U(this,a);this.J(a)&&(this.f-=this.c.get(a).length);this.c.set(a,[b]);this.f+=1;return this};h.get=function(a,b){a=a?this.D(a):[];return 0<a.length?String(a[0]):b};
h.toString=function(){if(this.i)return this.i;if(!this.c)return"";for(var a=[],b=this.c.N(),c=0;c<b.length;c++)for(var d=b[c],e=encodeURIComponent(String(d)),d=this.D(d),f=0;f<d.length;f++){var g=e;""!==d[f]&&(g+="="+encodeURIComponent(String(d[f])));a.push(g)}return this.i=a.join("&")};h.clone=function(){var a=new S;a.i=this.i;this.c&&(a.c=this.c.clone(),a.f=this.f);return a};var U=function(a,b){b=String(b);a.j&&(b=b.toLowerCase());return b};
S.prototype.ka=function(a){a&&!this.j&&(T(this),this.i=null,this.c.forEach(function(a,c){var b=c.toLowerCase();c!=b&&(this.remove(c),this.remove(b),0<a.length&&(this.i=null,this.c.set(U(this,b),za(a)),this.f+=a.length))},this));this.j=a};var cc,dc,V=function(){return k.navigator?k.navigator.userAgent:""},ec=v(V(),"Android"),fc=v(V(),"MSIE")||v(V(),"IEMobile")||v(V(),"Windows Phone");var W=function(a){E.call(this);this.da=a;this.b={}};u(W,E);var gc=[];W.prototype.listen=function(a,b,c,d){n(b)||(b&&(gc[0]=b.toString()),b=gc);for(var e=0;e<b.length;e++){var f=J(a,b[e],c||this.handleEvent,d||!1,this.da||this);if(!f)break;this.b[f.key]=f}return this};W.prototype.pa=function(a,b,c,d){return hc(this,a,b,c,d)};var hc=function(a,b,c,d,e,f){if(n(c))for(var g=0;g<c.length;g++)hc(a,b,c[g],d,e,f);else{b=L(b,c,d||a.handleEvent,e,f||a.da||a);if(!b)return a;a.b[b.key]=b}return a};
W.prototype.unlisten=function(a,b,c,d,e){if(n(b))for(var f=0;f<b.length;f++)this.unlisten(a,b[f],c,d,e);else c=c||this.handleEvent,e=e||this.da||this,c=tb(c),d=!!d,b=H(a)?a.O(b,c,d,e):a?(a=K(a))?a.O(b,c,d,e):null:null,b&&(zb(b),delete this.b[b.key]);return this};W.prototype.ha=function(){Aa(this.b,function(a,b){this.b.hasOwnProperty(b)&&zb(a)},this);this.b={}};W.prototype.s=function(){W.H.s.call(this);this.ha()};
W.prototype.handleEvent=function(){throw Error("EventHandler.handleEvent not implemented");};var X=function(){E.call(this);this.v=new I(this);this.wa=this;this.fa=null};u(X,E);X.prototype[jb]=!0;h=X.prototype;h.addEventListener=function(a,b,c,d){J(this,a,b,c,d)};h.removeEventListener=function(a,b,c,d){yb(this,a,b,c,d)};
h.dispatchEvent=function(a){var b,c=this.fa;if(c)for(b=[];c;c=c.fa)b.push(c);var c=this.wa,d=a.type||a;if(p(a))a=new F(a,c);else if(a instanceof F)a.target=a.target||c;else{var e=a;a=new F(d,c);Ca(a,e)}var e=!0,f;if(b)for(var g=b.length-1;!a.C&&0<=g;g--)f=a.currentTarget=b[g],e=ic(f,d,!0,a)&&e;a.C||(f=a.currentTarget=c,e=ic(f,d,!0,a)&&e,a.C||(e=ic(f,d,!1,a)&&e));if(b)for(g=0;!a.C&&g<b.length;g++)f=a.currentTarget=b[g],e=ic(f,d,!1,a)&&e;return e};
h.s=function(){X.H.s.call(this);this.v&&this.v.ha(void 0);this.fa=null};h.listen=function(a,b,c,d){return this.v.add(String(a),b,!1,c,d)};h.pa=function(a,b,c,d){return this.v.add(String(a),b,!0,c,d)};h.unlisten=function(a,b,c,d){return this.v.remove(String(a),b,c,d)};var ic=function(a,b,c,d){b=a.v.g[String(b)];if(!b)return!0;b=b.concat();for(var e=!0,f=0;f<b.length;++f){var g=b[f];if(g&&!g.F&&g.capture==c){var r=g.listener,z=g.U||g.src;g.S&&pb(a.v,g);e=!1!==r.call(z,d)&&e}}return e&&0!=d.ta};
X.prototype.O=function(a,b,c,d){return this.v.O(String(a),b,c,d)};var jc=function(a,b){X.call(this);this.V=a||1;this.I=b||k;this.ca=q(this.Ha,this);this.ea=t()};u(jc,X);h=jc.prototype;h.enabled=!1;h.o=null;h.Ha=function(){if(this.enabled){var a=t()-this.ea;0<a&&a<.8*this.V?this.o=this.I.setTimeout(this.ca,this.V-a):(this.o&&(this.I.clearTimeout(this.o),this.o=null),this.dispatchEvent("tick"),this.enabled&&(this.o=this.I.setTimeout(this.ca,this.V),this.ea=t()))}};h.start=function(){this.enabled=!0;this.o||(this.o=this.I.setTimeout(this.ca,this.V),this.ea=t())};
h.stop=function(){this.enabled=!1;this.o&&(this.I.clearTimeout(this.o),this.o=null)};h.s=function(){jc.H.s.call(this);this.stop();delete this.I};var nc=function(){if(fc&&window.external&&"notify"in window.external)return new kc;if(ec&&window.googleAdsJsInterface&&"notify"in window.googleAdsJsInterface)try{return window.googleAdsJsInterface.notify("gmsg://mobileads.google.com/noop"),new lc}catch(a){}return new mc},pc=function(){oc||(oc=nc());return oc},oc=null,qc=function(){};u(qc,E);
var rc=function(a){var b="gmsg://mobileads.google.com/"+a.qa,c=a.ra;a={};for(var d in c)a[d]=c[d];a["google.afma.Notify_dt"]=(new Date).getTime();d={};for(var e in a)d[encodeURIComponent(String(e))]=a[e];var b=[b],f;for(f in d)Sb(f,d[f],b);b[1]&&(f=b[0],e=f.indexOf("#"),0<=e&&(b.push(f.substr(e)),b[0]=f=f.substr(0,e)),e=f.indexOf("?"),0>e?b[1]="?":e==f.length-1&&(b[1]=void 0));return b.join("")},sc=function(a,b){this.ba=a;this.xa=b||1;this.ia=[];this.Z=new jc(this.xa);this.ya=new W(this);this.ya.listen(this.Z,
"tick",this.Fa);this.Ca=!0};u(sc,qc);sc.prototype.sendMessage=function(a){this.Ca?(this.ia.push(a),this.Z.enabled||(a=this.ia.shift(),this.ba(a),this.Z.start())):this.ba(a)};sc.prototype.Fa=function(){var a=this.ia.shift();a?this.ba(a):this.Z.stop()};var kc=function(){};u(kc,qc);kc.prototype.sendMessage=function(a){a=rc(a);window.external.notify(a)};var mc=function(){sc.call(this,this.Ga);this.w=null};u(mc,sc);
mc.prototype.Ga=function(a){if(!this.w){var b;b=document.createElement("IFRAME");b.id="afma-notify-"+(new Date).getTime();b.style.display="none";this.w=b}a=rc(a);this.w.src=a;this.w.parentNode||document.body.appendChild(this.w)};mc.prototype.s=function(){Ya(this.w);this.w=null;mc.H.s.call(this)};var lc=function(){};u(lc,qc);lc.prototype.sendMessage=function(a){a=rc(a);window.googleAdsJsInterface.notify(a);window.googleAdsJsInterface.DEBUG&&console.log(a)};var tc=null,uc=function(){};uc.prototype.Da=aa;uc.prototype.ga=function(a){this.Da(a)};var Y=function(){X.call(this);this.P=pc();tc||(tc=new uc);this.P=pc();var a=ha(ib,this.P);this.K?l(void 0)?a.call(void 0):a():(this.B||(this.B=[]),this.B.push(l(void 0)?q(a,void 0):a));this.A={}};u(Y,X);Y.prototype.sendMessage=function(a,b){var c;p(a)?c=new Lb(a,b):a instanceof Lb&&(c=a);"loading"==document.readyState?(a=q(this.P.sendMessage,this.P,c),L(k,"DOMContentLoaded",a,!1,this)):this.P.sendMessage(c)};
Y.prototype.ga=function(a,b){"onshow"==a&&"loading"==document.readyState?(a=q(vc,k,a,b),L(k,"DOMContentLoaded",a)):this.dispatchEvent(new Mb(new Lb(a,b),this))};Y.prototype.la=function(a,b,c){c=q(c,b);var d=q(function(a){c(a.type,a.Ea)},b);this.listen(a,d);this.A[a]||(this.A[a]={});this.A[a][b]=d};Y.prototype.sa=function(a,b){this.A[a]&&this.A[a][b]&&(this.unlisten(a,this.A[a][b]),delete this.A[a][b])};
var xc=function(a,b){k.AFMA_Communicator?k.AFMA_Communicator.sendMessage(a,b):wc(a,b)},wc=function(a,b){"loading"==document.readyState?(a=q(wc,null,a,b),L(k,"DOMContentLoaded",a,!1)):(a=new Lb(a,b),pc().sendMessage(a))},vc=function(a,b){k.AFMA_Communicator.ga(a,b)},yc=function(a,b,c,d){k.AFMA_Communicator.removeEventListener(a,b,c,d)},zc=function(a,b,c,d){k.AFMA_Communicator.addEventListener(a,b,c,d)},Ac=function(a,b,c){k.AFMA_Communicator.la(a,b,c)},Bc=function(a,b){k.AFMA_Communicator.sa(a,b)};
if(!k.AFMA_Communicator){m("AFMA_AddEventListener",zc,k);m("AFMA_RemoveEventListener",yc,k);m("AFMA_AddObserver",Ac,k);m("AFMA_RemoveObserver",Bc,k);m("AFMA_ReceiveMessage",vc,k);m("AFMA_SendMessage",xc,k);var Cc=new Y;m("AFMA_Communicator",Cc,k);m("AFMA_Communicator.addEventListener",Y.prototype.addEventListener,void 0);m("AFMA_Communicator.removeEventListener",Y.prototype.removeEventListener,void 0);m("AFMA_Communicator.addObserver",Y.prototype.la,void 0);m("AFMA_Communicator.removeObserver",Y.prototype.sa,
void 0);m("AFMA_Communicator.receiveMessage",Y.prototype.ga,void 0);m("AFMA_Communicator.sendMessage",Y.prototype.sendMessage,void 0)};var Dc=-1;zc("onshow",function(){Dc=t()});zc("onhide",function(){Dc=-1});var Ec=function(a,b){this.h=a;this.za=1==b},Fc=-1;
Ec.prototype.accept=function(a,b){var c=t(),d;d=D(this.h,"siriusFlagIntentfulClickDelay");d=isNaN(d)?1E3:parseInt(d,10);var e=Dc;return 0<e&&c-e<d||c-Fc<d||bb(this.h)&&(c=b?a.clientX-b.getBoundingClientRect().left:a.clientX,a=b?a.clientY-b.getBoundingClientRect().top:a.clientY,!this.za&&(d=this.h,e=d.force_google_width&&d.force_google_height?new Za(d.force_google_width,d.force_google_height):new Za(d.google_width,d.google_height),d=b?b.getBoundingClientRect().width:e.ua,b=b?b.getBoundingClientRect().height:
e.oa,e=$a(this.h),c<=e[0]||c>=d-e[2]||a<=e[1]||a>=b-e[3])||"interstitial_mb"==db(this.h)&&(b=ab(this.h),c<=b&&a<=b))?!1:!0};(function(){var a=!1;try{var b=Object.defineProperty({},"passive",{get:function(){a=!0}});window.addEventListener("test",null,b)}catch(c){}return a})();var Hc=function(a){Gc();this.enabled=Math.random()<a},Gc=k.performance&&k.performance.now?q(k.performance.now,k.performance):t;var Ic=function(a){Hc.call(this,a)};u(Ic,Hc);new Ic(1E-4);var Jc=function(a){this.Aa=eb(a)},Kc={button:8,headline:0,description:7,logo:9,product:9,url:1},Lc=function(a,b){var c=q(function(a){var c=2,d;for(d in b){var g=C(d),r=Kc[b[d]],z;if(z=null!=r)z=a,z="none"!=Fb(g,"display")&&"hidden"!=Fb(g,"visibility")&&"0"!=Fb(g,"opacity")?z.clientX>=g.offsetLeft&&z.clientY>=g.offsetTop&&z.clientX<=g.offsetWidth+g.offsetLeft&&z.clientY<=g.offsetHeight+g.offsetTop:!1;z&&(c=r)}return c},a);return q(function(a,b){if(this.Aa)da(ja)&&ja(a.id,c(b));else{var d=c(b),e=new P(a.href),
r=b.clientX;Q(e);e.m.set("nx",r);b=b.clientY;Q(e);e.m.set("ny",b);Q(e);e.m.set("nb",d);a.href=e.toString()}},a)},Mc=function(a){da(st)&&st(a.id)};x&&B(8);var Nc=function(){throw Error("Do not instantiate directly");};Nc.prototype.ma=null;Nc.prototype.toString=function(){return this.content};var Oc=function(){Nc.call(this)};u(Oc,Nc);(function(a){function b(a){this.content=a}b.prototype=a.prototype;return function(a,d){a=new b(String(a));void 0!==d&&(a.ma=d);return a}})(Oc);(function(a){function b(a){this.content=a}b.prototype=a.prototype;return function(a,d){a=String(a);if(!a)return"";a=new b(a);void 0!==d&&(a.ma=d);return a}})(Oc);zc("onshow",function(){});zc("onhide",function(){});var Pc=function(a){this.h=a;new Jc(a)},Qc=function(a,b,c){var d=new Ec(a.h);-1==Fc&&(Fc=t());J(b,"click",q(function(a){if(d.accept(a)){if((eb(this.h)||"true"==D(this.h,"siriusFlagEnableClickParams"))&&l(c)&&c(b,a),"true"==cb(this.h,"octagonSdkRequest")){var e=b.href,e=e.match(/^\/\//)?"http:"+e:e,e={a:"app",u:e},g;l(dc)||(l(cc)||(cc=v(V(),"afma-sdk-a")?!0:!1),dc=cc?(g=V().match(/afma\-sdk\-a\-v\.?([\d+\.]+)/))?g[1]:"":"");(g=dc)&&0<=ta(g,"8400000.0.0")&&Ca(e,{system_browser:!0,use_first_package:!0,
use_running_process:!0});xc("open",e);a.preventDefault()}}else a.preventDefault()},a),!1);eb(a.h)&&J(b,"mousedown",ha(Mc,b))};var Rc=function(a){var b=C("adContent"),c={};xa(b.childNodes,function(a){var b=a.getAttribute("data-type");b&&(c[a.id]=b)});var d=Hb(b,a.redirect_url,"_blank"==a.link_target?"_blank":"_top"),e=new Pc(a),f=new Jc(a);Qc(e,d,Lc(f,c));Kb(b,a)},Uc=function(a){var b=Sc,c=Tc;a.google_template_data.adData[0].siriusFlagClickAreaOption="none";window.renderAd(a,b,function(){Rc(a);c&&c()})};var Vc=["top","right","bottom","left"],Xc=function(a){return Wc("shape",a)},Wc=function(a,b,c){a={type:a,node_id:b};l(c)&&(a.field_name=c);return a},Z=function(a,b,c,d){var e={};e.element=a;a={type:"element"};a.spec=e;Yc(a,b,c,d);return a},Zc=function(a,b,c,d){var e={};e.elements=b;e.margin=c;b={};b.type=a;b.spec=e;Yc(b,"bottom",d,void 0);return b},Yc=function(a,b,c,d){if(4!=c.length)throw Error("The anchors should be an array of length 4.");b&&(a.alignments=b);for(b=0;b<Vc.length;++b)c[b]&&(a[Vc[b]]=
c[b]);l(d)&&(a.layer=d)};var $c={clickTFText:{displayType:"nessieButton"}},ad=Wc("logo","logo-image",void 0),bd=Wc("text","headline",void 0);bd.component_type="headline";var cd=Wc("text","description",void 0);cd.component_type="description";
var dd={product1MCImage:{type:"background_image",node_id:"adContent"},logoMCImage:ad,text1TFText:bd,text2TFText:cd,clickTFText:Wc("button","button",void 0),productCover:Xc("product-cover"),verticalBorder:Xc("border_vertical"),horizontalBorder:Xc("border_horizontal"),line:Xc("line"),arrow:Xc("arrow")},ed={calibrations:["AspectRatioGE 0.9 0.8"],logo:Z("logoMCImage","top",["7%","","70%",""]),button:Z("clickTFText","bottom",["","","15%","10%"]),headline:Z("text1TFText","top",["min(logo 6%, 15%)","10%",
"50%","10%"]),line:Z("line","top",["headline 0","headline right 0","line 2px","headline left 0"]),description:Z("text2TFText","top",["headline 20px","10%","button 6%","10%"])},fd={logo:Z("logoMCImage","top left",["7%","","70%","7%"]),button:Z("clickTFText","bottom",["logo","","15%",""]),headline:Z("text1TFText","top",["min(logo 6%, 15%)","10%","50%","10%"]),line:Z("line","top",["headline 0","headline right 0","line 2px","headline left 0"]),description:Z("text2TFText","top",["headline 20px","10%",
"button 6%","10%"])},gd={styles:{text1TFText:{padding:"5% 0%"},text2TFText:{padding:"5% 0%"}},calibrations:["AspectRatioLE 5.0 0.8"],logo:Z("logoMCImage","left",["10%","50%","10%",""]),headline:Z("text1TFText","left bottom",["10%","min(button 3%, 10%)","55%","min(logo 3%, 10%)"]),line:Z("line","top",["headline 0","headline right 0","line 2px","headline left 0"]),description:Z("text2TFText","left top",["headline 15px","min(button 3%, 10%)","10%","min(logo 3%, 10%)"]),button:Z("clickTFText","right",
["10%","3%","10%","50%"])},hd={calibrations:["AspectRatioLE 3.0 0.8"],styles:{text1TFText:{padding:"5% 0%"},text2TFText:{padding:"5% 0%"}},headline:Z("text1TFText","left bottom",["10%","min(logo, button, 15%)","55%","5%"]),line:Z("line","top",["headline 0","headline right 0","line 2px","headline left 0"]),description:Z("text2TFText","left top",["headline 15px","min(logo, button, 15%)","10%","5%"]),logo:Z("logoMCImage","right bottom",["20%","5%","40%","40%"]),button:Z("logoMCImage","top right",["63%",
"3%","10%","40%"])},id={calibrations:["AspectRatioLE 4 0"],logo:Z("logoMCImage","left",["","70%","",""]),text1:Z("text1TFText","left",["10%","50%","20%","logo 4%"]),text2:Z("text2TFText","",["10%","button","10%","text1 4%"]),button:Z("clickTFText","left right",["","","","80%"])},jd=Z("text1TFText","",["","","logoAndButton 10%",""]),kd=Z("text2TFText","",["","","logoAndButton 10%",""],1),ld;ld=Zc("vertical-list",["clickTFText","logoMCImage"],"auto",["60%","","",""]);
var md={styles:$c,text1:jd,text2:kd,logoAndButton:ld},nd=Z("text1TFText","",["10px","","logoAndButton 10%",""]),od=Z("text2TFText","",["10px","","logoAndButton 10%",""],1),pd;pd=Zc("horizontal-list",["logoMCImage","clickTFText"],"even_left",["50%","10%","10px","10%"]);
var Sc={elements:dd,styles:{text1TFText:{font_level:1,color:"text1TFTextColor",backgroundColor:"back1MCColor"},text2TFText:{font_level:2,color:"text2TFTextColor",backgroundColor:"back1MCColor"},clickTFText:{color:"clickTFTextColor",backgroundColor:"back1MCColor",weight:.05},productCover:{backgroundColor:"back1MCColor"},verticalBorder:{backgroundColor:"back2MCColor"},horizontalBorder:{backgroundColor:"back2MCColor"},line:{backgroundColor:"back1MCColor"},arrow:{backgroundColor:"back1MCColor"}},font_scale_strategy:"mega_title",
variations:{tower:ed,square:fd,banner1:gd,banner2:hd,banner3:id,smallTower:md,smallSquare:{styles:$c,text1:nd,text2:od,logoAndButton:pd},smallBanner:{styles:$c,logo:Z("logoMCImage","left",["","50%","","3%"]),text1:Z("text1TFText","left",["2px","button","2px","logo 7%"]),text2:Z("text2TFText","left",["2px","button","2px","logo 7%"],1),button:Z("clickTFText","right",["","","","50%"])}}},Tc=function(){var a=document.getElementById("adContent").getAttribute("data-variation"),b=document.getElementById("adContent"),
c=parseInt(b.style.width,10),b=parseInt(b.style.height,10),d=document.getElementById("border_vertical"),e=document.getElementById("border_horizontal"),f=Math.floor(.02*Math.sqrt(c*b));d.style.borderColor=d.style.backgroundColor;d.style.borderLeftWidth=f+"px";d.style.borderRightWidth=f+"px";d.style.margin=f+"px";d.style.width=c-4*f+"px";d.style.height=b-2*f+"px";d.style.backgroundColor="transparent";e.style.borderColor=e.style.backgroundColor;e.style.borderTopWidth=f+"px";e.style.borderBottomWidth=
f+"px";e.style.margin=f+"px";e.style.width=c-2*f+"px";e.style.height=b-4*f+"px";e.style.backgroundColor="transparent";b=document.getElementById("arrow");b.innerHTML='<svg id="arrowIcon" viewBox="0 0 17 20"><polygon points="3,0 0,3 7,10 0,17 3,20 13,10"/></svg>';c=document.getElementById("button");d=parseInt(c.style.top,10);e=parseInt(c.style.left,10);f=parseInt(c.style.height,10);if(-1<["smallTower","smallSquare","smallBanner"].indexOf(a)||!f||e<f)b.style.display="none";var g=.6*f;b.style.width=g+
"px";b.style.height=g+"px";b.style.top=d+(f-g)/2+"px";b.style.left=e-g/2+"px";b.style.backgroundColor="transparent";b=document.getElementById("arrowIcon");b.style.width="100%";b.style.height="100%";b.childNodes[0].style.fill=c.style.color;(c=document.getElementById("button"))&&-1==a.indexOf("small")&&(c.style.backgroundColor="rgba(0, 0, 0, 0)");document.getElementById("line").style.backgroundColor=document.getElementById("headline").style.color};m("onAdData",function(a){Uc(a)},void 0);}).call(this);
