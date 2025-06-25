//
//  zaniaFilterExtensionMainView.swift
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

import SwiftUI

struct zaniaFilterExtensionMainView: View {
    var parameterTree: ObservableAUParameterGroup
    let placeHolderImage = UIImage(named: "Logo")
    
    var body: some View {
        VStack(alignment: .center){
            Image(.logo).resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 300, alignment: .top)
                .padding([.top, .trailing], 20)
            
            HStack{
                ArcKnobView(param: parameterTree.global.gain)
                ArcKnobView(param: parameterTree.global.pan)
                ArcKnobView(param: parameterTree.global.cutoff)
                ArcKnobView(param: parameterTree.global.temp)
            }
            
        }
    }
}
