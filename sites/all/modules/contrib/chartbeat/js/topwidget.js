
function topwidget(apikey, host, divid, theme, limit)
{
  this.apikey = apikey;
  this.divid = divid;
  this.theme = theme;
  this.limit = limit;
  this.host = host;

  if (!this.theme)
    this.theme = "";

  if (!this.limit)
    this.limit = 5;

  var thisobj = this;

  var jsonp = 'topwidget.cback' + Math.round(Math.random()*10000000);
  eval(jsonp + "= function(data) { thisobj.draw(data); }");

  //this.host = location.host;

  var dataurl = 'http://api.chartbeat.com/live/toppages/v3/?host='+this.clean_domain(this.host)+'&jsonp=' + jsonp + '&apikey=' + apikey + "&limit=" + this.limit;

  var headID = document.getElementsByTagName("head")[0];
  var newScript = document.createElement('script');
  newScript.type = 'text/javascript';
  newScript.src = dataurl;
  headID.appendChild(newScript);
}

topwidget.sort = function(a, b)
{
  if (a["count"] > b["count"])
    return -1;
  if (a["count"] < b["count"])
    return 1;

  return 0;
}

topwidget.prototype.draw = function(data)
{
  var themes = { '': { 'bgcolor': 'f0f7ea', 'border': 'dde7d4' },
		 'blue': { 'bgcolor': 'c4e3eb', 'border': '77a0ab' },
		 'silver': { 'bgcolor': 'e7e7e7', 'border': 'cccccc' },
		 'green': { 'bgcolor': 'c6dfa7', 'border': 'bdc1a3' },
		 'rose': { 'bgcolor': 'f5c5be', 'border': 'e1cab1' }
               }

  var html = '<table border="0" cellpadding="0" cellspacing="0" style="background-color:#'+themes[this.theme]['bgcolor']+'; border: 1px solid #'+themes[this.theme]['border']+'; width: 200px; -moz-border-radius: 15px;-webkit-border-radius: 15px;"><tr><td style="text-align:center;color:#555555;font-size:18px; padding-bottom: 10px;">Most popular pages on '+this.clean_domain(this.host)+'</td></tr>';

  if (!data.length)
    html += '<tr><td style="padding:5px; font-size: 14px; text-align: center;">currently no pages listed</td></tr>';

  for (var x = 0; x < data.length && x < this.limit; ++x)
  {
    html += '<tr>';

    var title = data[x]["i"];
    if (!title)
      title = data[x]["path"];

    var people = (data[x]["visitors"] == 1) ? '1 person' : data[x]["visitors"] + ' people';

    html += '<td style="padding:5px; padding-left: 10px"><a href="http://' + this.clean_path(data[x]["path"],this.host) + '" style="color: #5469d5; font-size: 12px; text-decoration:none;">' + this.truncate(title, 33) + '</a><div style="font-size:10px; float: right;">currently '+people+'</div></td>';

    html += '</tr>';
  }

  html += '</table><div style="font-size:8px; text-align: right; width: 200px; color: #aaa"><a href="http://chartbeat.com" style="font-size:8px;color:#aaa; text-decoration:none;" target="_blank">powered by chartbeat</a></div>';

  if (this.divid)
    document.getElementById(this.divid).innerHTML = html;
  else
    document.write(html);
}

topwidget.prototype.truncate = function(str, len)
{
  if (str.length <= len)
    return str;

  return str.substr(str, len - 3) + "...";
}

topwidget.prototype.clean_domain = function(domain)
{
  domain = domain.replace(/^https?:\/\//i,'');
  domain = domain.replace(/\s*/g,'');
  domain = domain.replace(/^(www.)/i,'');
  domain = domain.replace(/\/.*/g,'');
  domain = domain.replace(/[^0-9A-Za-z.-]*/g,'');

  return domain;
}

topwidget.prototype.clean_path = function(path,domain)
{
  if (path.search(/\.[A-Z,a-z]*\//) == -1)
    return this.clean_domain(domain) + path;
  else
    return path;
}
