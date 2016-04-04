 // remove elements
Element.prototype.remove = function () {
    this.parentElement.removeChild(this);
}

NodeList.prototype.remove = HTMLCollection.prototype.remove = function() {
    for (var i = this.length - 1; i >= 0; i--) {
        if(this[i] && this[i].parentElement) {
            this[i].parentElement.removeChild(this[i]);
        }
    }
}

$(function() { 
    // get the db file
    var fs   = require("fs"),
        file = "../build/memory.db";
    
    // check if db exist 
    if(!fs.existsSync(file)) {
        alert("DB is not present");
        getDbFile();
        
    } else { 
        chartData(file);
    }
});

// function to locate the sqlite db (need to get full path of fb)
function getDbFile() {
    var path = require('path');
    var dropZone = document.getElementById('drop-zone');
    
     dropZone.ondrop = function(e) {
        var data = e.dataTransfer.getData('text/plain');
        e.preventDefault();
        this.className = 'upload-drop-zone';
         
        chartData(e.dataTransfer.files[0].name); // need to get full path
    }
     
    dropZone.ondragover = function() {
        this.className = 'upload-drop-zone drop';
        return false;
    }

    dropZone.ondragleave = function() {
        this.className = 'upload-drop-zone';
        return false;
    }
}

// function that get data from db and charts
function chartData(filename) {
    // get the canvas
    var memory_chart = document.getElementById('memory_chart').getContext('2d');
    // db located, remove the upload drop zone
    document.getElementsByClassName("upload-drop-zone").remove();
        
    // create the db object
    var dblite = require('dblite'),
        db     = dblite(filename);
    
    // get all data from the db
    db.query('SELECT total, used, available, time FROM memory', ['total', 'used', 'available', 'time'], function(rows) {
        rows.forEach(eachRow);
    });
        
    // push data in local arrays 
    var usedMemory = [0];
    var memoryFree = [0];
    var totalMemory = [0];
    var timeStamp = [0];

    function eachRow(row, i, rows) {
        memoryFree.push(row.available);
        totalMemory.push(row.total);
        usedMemory.push(row.used);
        timeStamp.push(row.time);

        if ((i + 1) === rows.length) {
            start = Date.now() - start;
            console.log(start);
            db.close();
        }
    }  
            
    alert("Data loaded..");
            
    // extend line to get a y label
    Chart.types.Line.extend({
        name: "LineAlt",
        draw: function () {
            Chart.types.Line.prototype.draw.apply(this, arguments);

            var ctx = this.chart.ctx;
            ctx.save();
            // text alignment and color
            ctx.textAlign = "center";
            ctx.textBaseline = "bottom";
            ctx.fillStyle = this.options.scaleFontColor;
            // position
            var x = this.scale.xScalePaddingLeft * 0.4;
            var y = this.chart.height / 2;
            // change origin
            ctx.translate(x, y)
            // rotate text
            ctx.rotate(-90 * Math.PI / 180);
            ctx.fillText(this.datasets[0].label, 0, 0);
            ctx.restore();
        }
    });
            
    // draw chart
    var memoryInfo = {
        labels : timeStamp,
        datasets : [{
                label: "Free [Mb]",
                fillColor : "rgba(132, 153, 194, 0.53)",
                strokeColor : "#4563c6",
                pointColor : "#fff",
                pointStrokeColor : "rgb(95, 130, 186)",
                data : memoryFree
        }, {
                label: "Total",
                fillColor: "rgba(220, 220, 220, 0.31)",
                strokeColor: "rgba(220,220,220,1)",
                pointColor: "rgba(220,220,220,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(220,220,220,1)",
                data : totalMemory
        }, {
                label: "Used",
                fillColor: "rgba(151,187,205,0.2)",
                strokeColor: "rgba(151,187,205,1)",
                pointColor: "rgba(151,187,205,1)",
                pointStrokeColor: "#fff",
                pointHighlightFill: "#fff",
                pointHighlightStroke: "rgba(151,187,205,1)",
                data : usedMemory 
        }]
    };
    
    new Chart(memory_chart).LineAlt(memoryInfo, {
        scaleLabel: "          <%=value%>"
    });
}