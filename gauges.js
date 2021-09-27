/*
 * This file is part of the esp8266 web interface
 *
 * Copyright (C) 2018 Johannes Huebner <dev@johanneshuebner.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

var gauges = {};
var items = new Array();

function onLoad()
{
    createGauges();
  /*  setInterval(acquire, 500) */
    acquire(); 
}

/**
 * @brief Creates gauges for all canvases found on the page
 */
function createGauges()
{
	var div = document.getElementById("gauges");
	var paramPart = document.location.href.split("items=");
	items = paramPart[1].split(",");
	
	for (var i = 0; i < items.length; i++)
	{
		var name = items[i];
		var canvas = document.createElement("CANVAS");
		canvas.setAttribute("id", name);
		div.appendChild(canvas);
		
		var min = 0;
		var max = 1;
		var gtitle = name
		
		//special scaling for certain guages
		if(name == "vbat")
		{
		  var gauge = new RadialGauge( 
		  { 
			renderTo: name, 
			title: "Voltage",
			width: 400, 
			height: 400, 
			minValue: 44, 
			maxValue: 60,
			majorTicks: [0, 1],
			colorBorderOuter: '#555',
			highlights: [
                { from: 58, to: 60, color: 'rgba(255,0,0,1)' },
                { from: 51, to: 58, color: 'rgba(0,255,0,.15)' },
                { from: 48, to: 51, color: 'rgba(255,255,0,.15)' },             
                { from: 44, to: 48, color: 'rgba(255,0,0,.25)' }
                ]
		  });
		}
		else
		{
		  if(name == "tbat")
		  {
		      var gauge = new RadialGauge( 
		      { 
			     renderTo: name, 
			     title: "Temperature",
			     units: "°C",
			     width: 400, 
			     height: 400, 
			     minValue: -5, 
			     maxValue: 60,
			     majorTicks: [0, 1],
			     highlights: [
                        { from: 40, to: 60, color: 'rgba(255,0,0,.25)' },
                        { from: 4, to: 40, color: 'rgba(0,255,0,.15)' },             
                        { from: -5, to: 4, color: 'rgba(0,0,255,.5)' }
                        ]
		      });
		      
		  }
		  else
		  {
		      if(name == "ibat")
		      {
		          var gauge = new RadialGauge( 
		          { 
			         renderTo: name, 
			         title: "Current",
			         units: "Amps",
			         width: 400, 
			         height: 400, 
			         minValue: -40, 
			         maxValue: 400,
			         majorTicks: [0, 1],
			         highlights: [
                        { from: -40, to: 0, color: 'rgba(255,0,0,.15)' },
                        { from: 0, to: 400, color: 'rgba(0,255,0,.15)' }
                        ]
		          });
		      }
		      else
		      {
		          if(name == "cbat")
		          {
		              min = 0;
		              max = 250;
		              gtitle = "Charge in Ah";
		          }
		          else
		          {
		              min = 0;
		              max = 1;
		          }
		          var gauge = new RadialGauge( 
		          { 
			         renderTo: name, 
			         title: gtitle,
			         width: 400, 
			         height: 400, 
			         minValue: min, 
			         maxValue: max,
			         majorTicks: [0, 1],
			         highlights: [ ]	
	               });
		          
		      }   
		       
		      
		  }
		  
        }
		
		

		gauge.draw();
		gauges[name] = gauge;
	}
}

function calcTicks(min, max)
{
	var N = 6;
	var ticks =  [ min ];
	var dist = (max - min) / N;
	var tick = min;
	
	for (var i = 0; i < N; i++)
	{
		tick += dist;
		ticks.push(Math.round(tick));
	}
	return ticks;
}

function acquire()
{
	if (!items.length) return;

	inverter.getValues(items, 1,
	function(values) 
	{
		for (var name in values)
		{
			var val = values[name][0];
			//gauges[name].options.minValue = Math.min(gauges[name].options.minValue, Math.floor(val * 0.7));
			//gauges[name].options.maxValue = Math.max(gauges[name].options.maxValue, Math.ceil(val * 1.5));
			gauges[name].options.majorTicks = calcTicks(gauges[name].options.minValue, gauges[name].options.maxValue);
			gauges[name].value = val;
			gauges[name].update();
		}
		setTimeout(acquire, 500); 
	});
}
