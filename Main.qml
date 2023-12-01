import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

//import QtQuick.Controls.Basic
//import QtQuick.Controls.Material
Window {
    width: 700
    height: 480
    visible: true
    title: qsTr("Hello World")

    Component.onCompleted: {
        u64RepText.color = "black"
        f64rawdatas.m_u64Str = 0
        u64RepText.text="0"
        s64RepText.text="0"
        f64RepText.text="0"
        f64HexRepText.text = "0x0"

        //e5m2RepText.color = "black"
        //e5m2_f64rawdatas.m_u64Str = 0
        //e5m2_u8RepText.text="0"
        //e5m2_s8RepText.text="0"
        e5m2_bf8RepText.text="0.0"
        e5m2HexRepText.text = "0x0"
    }

    Connections {
        target: f64rawdatas
        function onUpdateUi() {
            u64RepText.text = f64rawdatas.m_u64Str
            s64RepText.text = f64rawdatas.m_s64Str
            f64RepText.text = f64rawdatas.m_f64Str
            f64HexRepText.text = f64rawdatas.m_f64Hex

            for (var idx = 0; idx < 64; idx++) {
                f64bits.itemAt(63-idx).children[0].checked = f64rawdatas.getf64BitsbyIdx(idx);
            }
        }
    }
    Connections {
        target: e5m2rawdatas
        function onUpdateUi() {
            //u64RepText.text = f64rawdatas.m_u64Str
            //s64RepText.text = f64rawdatas.m_s64Str
            e5m2_bf8RepText.text = e5m2rawdatas.m_e5m2Str
            e5m2HexRepText.text = e5m2rawdatas.m_e5m2Hex

            for (var idx = 0; idx < 7; idx++) {
                e5m2bits.itemAt(7-idx).children[0].checked = e5m2rawdatas.gete5m2BitsbyIdx(idx);
            }
        }
      }
    //property var isChecked: new Array(64).fill(false)
ColumnLayout{
    //f64 bits
    ColumnLayout {
        GridLayout {
            id: grid
            columns: 32
            columnSpacing: 0
            Layout.margins: 0
            Repeater {
            id: f64bits
                model: 64
                ColumnLayout {
                    spacing: 0
                    CheckBox {
                        //checked: isChecked[63 - index]
                        onCheckedChanged: {
                            //isChecked[63 - index] = checked // 更新数组元素的值
                            f64rawdatas.setF64RawbyBit(checked, 63 - index)
                        }
                    }
                    Label {
                        text: qsTr("" + (63 - index))
                    }
                }
            }
        }

        GridLayout {
            columns: 2
            Label {
                text: "Hexadecimal Representation"
            }
            TextField {
                id: f64HexRepText
                implicitWidth:400
                color: "black"
                onTextChanged: {
                }
            }

            Label {
                text: "Unsigned Integer Representation"
            }
            TextField {
                id: u64RepText
                validator: RegularExpressionValidator { regularExpression:/^[1-9][0-9]{0,18}$/}
                implicitWidth:400
                color: "black"
                onTextChanged: {
                    f64rawdatas.setF64RawbyU64Str(text)
                }
            }

            Label {
                text: "Signed Integer Representation"
            }
            TextField {
                id: s64RepText
                validator: RegularExpressionValidator { regularExpression:/^[-+]?[0-9]{1,19}$/}
                implicitWidth:400
                color: "black"
                onTextChanged: {
                    f64rawdatas.setF64RawbyS64Str(text)
                }
            }

            Label {
                text: "Float Representation"
            }
            TextField {
                id: f64RepText
                implicitWidth:400
                color: "black"
                onTextChanged: {
                }
            }
        }
    }

    //e5m2 bits
    ColumnLayout {
            GridLayout {
                //id: grid
                columns: 32
                columnSpacing: 0
                Layout.margins: 0
                Repeater {
                id: e5m2bits
                    model: 8
                    ColumnLayout {
                        spacing: 0
                        CheckBox {
                            //checked: isChecked[7 - index]
                            onCheckedChanged: {
                                //isChecked[63 - index] = checked // 更新数组元素的值
                                e5m2rawdatas.sete5m2RawbyBit(checked, 7 - index)
                            }
                        }
                        Label {
                            text: qsTr("" + (7 - index))
                        }
                    }
                }
            }

            GridLayout {
                columns: 2
                Label {
                    text: "Hexadecimal Representation"
                }
                TextField {
                    id: e5m2HexRepText
                    implicitWidth:400
                    color: "black"
                    onTextChanged: {
                    }
                }

                Label {
                    text: "Unsigned Integer Representation"
                }
                TextField {
                    id: e5m2_bf8RepText
                    validator: RegularExpressionValidator { regularExpression:/^[1-9][0-9]{0,18}$/}
                    implicitWidth:400
                    color: "black"
                    onTextChanged: {
                        //f64rawdatas.setF64RawbyU64Str(text)
                    }
                }

                Label {
                    text: "Signed Integer Representation"
                }
                TextField {
                    id: e5m2_s8RepText
                    validator: RegularExpressionValidator { regularExpression:/^[-+]?[0-9]{1,19}$/}
                    implicitWidth:400
                    color: "black"
                    onTextChanged: {
                        f64rawdatas.setF64RawbyS64Str(text)
                    }
                }

                Label {
                    text: "Float Representation"
                }
                TextField {
                    id: e5m2_f8RepText
                    implicitWidth:400
                    color: "black"
                    onTextChanged: {
                    }
                }
            }
        }
}
}
