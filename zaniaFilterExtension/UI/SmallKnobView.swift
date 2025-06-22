//
//  ParameterSlider.swift
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//
import Controls
import SwiftUI

struct SmallKnobView: View {
    @State var value: Float = 0.33

    var body: some View {
        GeometryReader { proxy in
            VStack(alignment: .leading, spacing: 20) {

                HStack(alignment: .center, spacing: 50) {
                    SmallKnob(value: $value)
                        .backgroundColor(.yellow)
                        .foregroundColor(.blue)
                    SmallKnob(value: $value)
                        .backgroundColor(.orange)
                        .foregroundColor(.red)
                    SmallKnob(value: $value)
                }
            }
        }
        .padding()
    }
}
