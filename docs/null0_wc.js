// this will setup the web-component
/* global HTMLElement */

import setupCart from './null0.js'

export default class Null0WebComponent extends HTMLElement {
  constructor () {
    super()
    this.shadow = this.attachShadow({ mode: 'open' })
    this.canvas = document.createElement('canvas')
    this.shadow.appendChild(this.canvas)

    if (!this.attributes?.src?.value) {
      throw new Error('src attribute is required, and should point to your cart URL.')
    }

    setupCart(this.attributes.src.value, this.canvas).then(({ host, cart }) => {
      this.host = host
      this.cart = cart
      if (this.attributes?.fps) {
        const ctx = this.host.canvas.getContext('2d')
        ctx.font = '16px Arial'
        let t = Date.now()
        let o = t
        let d = 0
        let fps = 60
        const updateTime = 500
        this.cart.frameCallback = () => {
          if (t - o > updateTime) {
            d = Date.now() - t
            o = t
            fps = parseInt(1000 / d)
          }
          t = Date.now()

          ctx.fillStyle = 'black'
          ctx.fillText(fps, 9, 19)
          ctx.fillStyle = 'black'
          ctx.fillText(fps, 11, 21)
          ctx.fillStyle = 'white'
          ctx.fillText(fps, 10, 20)
        }
      }
    })
  }
}

document.addEventListener('DOMContentLoaded', () => {
  window.customElements.define('null0-cart', Null0WebComponent)
})
