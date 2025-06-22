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
        ParameterSlider(param: parameterTree.global.gain)
    }
}
