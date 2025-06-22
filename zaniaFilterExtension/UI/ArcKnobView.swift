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
    
    @State var volume: Float = 0.33
    @State var pan: Float = 0.33
    @State var cutoff: Float = 0

    var body: some View {
        GeometryReader { proxy in
            VStack(alignment: .leading, spacing: 40) {
                VStack(alignment: .center) {
                    ArcKnob("GAIN", value: $param.value, range: 0...1.0)
                        .backgroundColor(.yellow)
                        .foregroundColor(.blue)
                    ArcKnob("FREQ", value: $cutoff, range: 0...100, origin: 50)
                        .backgroundColor(.orange)
                        .foregroundColor(.red)
                    ArcKnob("PAN", value: $pan, range: -50...50)
                        .foregroundColor(.accentColor)
                }
            }
        }
        .navigationTitle("Arc Knob")
        .padding()
    }
}
