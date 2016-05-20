function debug(nickname,message) {
    var messageElement = document.createElement("article");
    messageElement.className = "alert alert-success";
    messageElement.innerHTML = message;
    var nicknameElement = document.createElement("span");
    nicknameElement.className = "navbar-right";
    nicknameElement.innerHTML = nickname;
    var sectionElement = document.getElementById("message-section");
    sectionElement.insertBefore(messageElement, sectionElement.firstChild).appendChild(nicknameElement);
}

function sendMessage() {
    var nickname = document.getElementById("inputNick").value;
    var message = document.getElementById("inputText").value;
    var strToSend = nickname + ": " + message;
    if ( websocket != null ) {
        document.getElementById("inputText").value = "";
        websocket.send( strToSend );
        console.log( "string sent :", '"'+strToSend+'"' );
        debug(nickname,message);
    }
}

var wsUri = "ws://localhost:55555";
var websocket = null;

function initWebSocket() {
    try {
        if (typeof MozWebSocket == 'function')
            WebSocket = MozWebSocket;
        if ( websocket && websocket.readyState == 1 )
            websocket.close();
        websocket = new WebSocket( wsUri );
        websocket.onopen = function (evt) {
            debug("System","Вы успешно присоеденились");
        };
        websocket.onclose = function (evt) {
            debug("System","Выход выполнен");
        };
        websocket.onmessage = function (evt) {
            console.log( "Message received :", evt.data );
            debug("System", evt.data );
        };
        websocket.onerror = function (evt) {
            debug("System",'Ошибка: ' + evt.data);
        };
    } catch (exception) {
        debug("System",'Исключение: ' + exception);
    }
}

function stopWebSocket() {
    if (websocket)
        websocket.close();
}

function checkSocket() {
    if (websocket != null) {
        var stateStr;
        switch (websocket.readyState) {
            case 0: {
                stateStr = "CONNECTING";
                break;
            }
            case 1: {
                stateStr = "OPEN";
                break;
            }
            case 2: {
                stateStr = "CLOSING";
                break;
            }
            case 3: {
                stateStr = "CLOSED";
                break;
            }
            default: {
                stateStr = "UNKNOW";
                break;
            }
        }
        debug("System","WebSocket state = " + websocket.readyState + " ( " + stateStr + " )");
    } else {
        debug("System","WebSocket is null");
    }
}
