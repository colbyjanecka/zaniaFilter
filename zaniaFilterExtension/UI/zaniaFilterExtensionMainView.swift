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
    @State var index1 = 0
    
    var body: some View {
        VStack(alignment: .center){
            Image(.logo).resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 300, alignment: .top)
                .padding([.top, .trailing], 20)
            
            HStack{
                ArcKnobView(param: parameterTree.global.gain)
                ArcKnobView(param: parameterTree.global.pan)
                ArcKnobView(param: parameterTree.global.temp)
                ArcKnobView(param: parameterTree.global.delayTime)
                ArcKnobView(param: parameterTree.global.decayFactor)
            }
            GroupBox(){
                IndexedSlider(index: $index1, labels: ["1 Pole", "2 Pole", "3 Pole", "4 Pole"])
                    .backgroundColor(.main)
                    .foregroundColor(.accent)
            }.padding([.leading, .trailing, .bottom], 50)
            
        }
    }
}
