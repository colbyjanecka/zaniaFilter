//
//  zaniaFilterExtensionMainView.swift
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

import SwiftUI

struct zaniaFilterExtensionMainView: View {
    var parameterTree: ObservableAUParameterGroup
    
    var body: some View {
        VStack(alignment: .center){
            HStack{
                ArcKnobView(param: parameterTree.global.gain)
                ArcKnobView(param: parameterTree.global.pan)
            }
            
        }
    }
}
