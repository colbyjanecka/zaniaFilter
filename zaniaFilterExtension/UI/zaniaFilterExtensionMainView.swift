//
//  zaniaFilterExtensionMainView.swift
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

import SwiftUI
import Controls

struct zaniaFilterExtensionMainView: View {
    var parameterTree: ObservableAUParameterGroup
    let placeHolderImage = UIImage(named: "Logo")
    var containerWidth:CGFloat = UIScreen.main.bounds.width - 32.0
    @State var index1 = 0
    
    var body: some View {
        VStack(alignment: .center){
            Image(.logo).resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 300, alignment: .top)
                .padding([.top, .trailing], 10)
            
            HStack{
                ArcKnobView(param: parameterTree.global.gain)
                ArcKnobView(param: parameterTree.global.pan)
                ArcKnobView(param: parameterTree.global.temp)
            }
            GroupBox(
                label: Label("Reverb", systemImage: "waveform")
                .foregroundColor(.main)
            ){
                HStack{
                    ArcKnobView(param: parameterTree.global.decay)
                    ArcKnobView(param: parameterTree.global.delayTime)
                }
            }.aspectRatio(3/2, contentMode: .fit)
                .frame(minWidth: containerWidth * 0.7, maxWidth: containerWidth, minHeight: 80, maxHeight: 300)
                .padding([.bottom, .leading, .trailing], 20)
        }
    }
}

