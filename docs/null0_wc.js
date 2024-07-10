// this will setup the web-component

import setupCart from './null0.js'

export default class Null0WebComponent extends HTMLElement {
  constructor() {
    super()
    this.shadow = this.attachShadow({ mode: 'open' })
    this.canvas = document.createElement('canvas')
    this.shadow.appendChild(this.canvas)

    if (!this.attributes?.src?.value) {
      throw new Error('src attribute is required, and should point to your cart URL.')
    }
    setupCart(this.attributes.src.value, this.canvas).then(({host, cart}) => {
      this.host = host
      this.cart = cart
    })
  }
}

document.addEventListener('DOMContentLoaded', () => {
  window.customElements.define('null0-cart', Null0WebComponent)
})