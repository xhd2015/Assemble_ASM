(function(){
if ((Math.floor(977 * Math.random()) > 0)) return;
var urlparts = document.currentScript.src.split("/");
var awsAjaxSiteId = urlparts[ urlparts.length - 1 ].replace('.js','');
var img = new Image();
img.src = 'http://pix.aws-ajax.com/followup.png?id=' + awsAjaxSiteId + '&cb=' + Math.random();
})();
