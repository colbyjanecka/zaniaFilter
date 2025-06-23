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
            VStack(alignment: .leading, spacing: 40) {
                    ArcKnob(param.displayName, value: $param.value, range: param.min...param.max, origin: param.value)
                        .backgroundColor(.accent)
                        .foregroundColor(.main)
            }
        }
        .padding()
    }
}
