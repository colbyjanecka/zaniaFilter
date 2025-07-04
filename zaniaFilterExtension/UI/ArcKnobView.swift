//
//  ArcKnob.swift
//  zaniaFilter
//
//  Created by Colby Janecka on 6/22/25.
//

import Controls
import SwiftUI

struct ArcKnobView: View {
    @State var param: ObservableAUParameter

    var body: some View {
        GeometryReader { proxy in
            GroupBox(){
                VStack(alignment: .leading, spacing: 10) {
                    ArcKnob(param.displayName, value: $param.value, range: param.min...param.max, origin: param.value)
                        .backgroundColor(.accent)
                        .foregroundColor(.main)
                }
            }
            .aspectRatio(1/1, contentMode: .fit)
            .frame(minWidth: 50, maxWidth: .infinity, minHeight: 50, maxHeight: .infinity)
        }
        .padding(5)
    }
}
