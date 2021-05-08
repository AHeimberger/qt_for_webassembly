import QtQml 2.2
import QtQuick 2.0

Canvas {
    id: canvas

    property real arcBegin: 0
    property real arcEnd: 270
    property real lineWidth: 4
    property string lineColor: "#FF0000"

    onPaint: {
        var ctx = getContext("2d")
        var x = canvas.width / 2
        var y = canvas.height / 2
        var start = Math.PI * (canvas.arcBegin / 180)
        var end = Math.PI * (canvas.arcEnd / 180)
        ctx.reset()

        ctx.beginPath();
        ctx.arc(x, y, (canvas.width / 2) - canvas.lineWidth / 2, start, end, false)
        ctx.lineWidth = canvas.lineWidth
        ctx.strokeStyle = canvas.lineColor
        ctx.stroke()
    }
}
