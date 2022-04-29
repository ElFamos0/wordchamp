<script setup>
import Keyboard from 'simple-keyboard';
import 'simple-keyboard/build/css/index.css';
import {onMounted, ref, defineEmits, defineProps, watch} from 'vue';

const emit = defineEmits(["onKeyPress"]);

const keyboard = ref(null);

const props = defineProps({
  guessedletter: Object,
});

// console.log(props.guessedletter)
const onKeyPress = (button) => {
  emit("onKeyPress", button)
}

onMounted(() => {
  keyboard.value = new Keyboard("simple-keyboard", {
    layout: {
    default: [
      'A Z E R T Y U I O P',
      'Q S D F G H J K L M',
      '{enter} W X C V B N {bksp}',
      ],
    },
    onKeyPress: onKeyPress,
    theme: "hg-theme-default hg-layout-default myTheme",
    buttonTheme: [
      {
        class: "hg-red",
        buttons: "A Z E R T Y U I O P Q S D F G H J K L M W X C V B N {bksp} {enter}",
      }
    ],
    display:{
      '{enter}': '<svg class="svg-inline--fa fa-check" aria-hidden="true" focusable="false" data-prefix="fas" data-icon="check" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512" data-v-a8932f12=""><path class="" fill="currentColor" d="M438.6 105.4C451.1 117.9 451.1 138.1 438.6 150.6L182.6 406.6C170.1 419.1 149.9 419.1 137.4 406.6L9.372 278.6C-3.124 266.1-3.124 245.9 9.372 233.4C21.87 220.9 42.13 220.9 54.63 233.4L159.1 338.7L393.4 105.4C405.9 92.88 426.1 92.88 438.6 105.4H438.6z"></path></svg>',
      '{bksp}': '<svg class="svg-inline--fa fa-delete-left" aria-hidden="true" focusable="false" data-prefix="fas" data-icon="delete-left" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 576 512" data-v-a8932f12=""><path class="" fill="currentColor" d="M576 384C576 419.3 547.3 448 512 448H205.3C188.3 448 172 441.3 160 429.3L9.372 278.6C3.371 272.6 0 264.5 0 256C0 247.5 3.372 239.4 9.372 233.4L160 82.75C172 70.74 188.3 64 205.3 64H512C547.3 64 576 92.65 576 128V384zM271 208.1L318.1 256L271 303C261.7 312.4 261.7 327.6 271 336.1C280.4 346.3 295.6 346.3 304.1 336.1L352 289.9L399 336.1C408.4 346.3 423.6 346.3 432.1 336.1C442.3 327.6 442.3 312.4 432.1 303L385.9 256L432.1 208.1C442.3 199.6 442.3 184.4 432.1 175C423.6 165.7 408.4 165.7 399 175L352 222.1L304.1 175C295.6 165.7 280.4 165.7 271 175C261.7 184.4 261.7 199.6 271 208.1V208.1z"></path></svg>', 
    }

  });
});

watch( () => props.guessedletter, (guessedletter) => {
  // console.log("j'update le clavier")
  keyboard.value.addButtonTheme(
    guessedletter.miss.join(" "),
    "miss"
  );
  keyboard.value.addButtonTheme(
    guessedletter.misplace.join(" "),
    "misplace"
  );  
  keyboard.value.addButtonTheme(
    guessedletter.found.join(" "),
    "found"
  );
},
  { deep: true }
);
      
</script>
<template>

<div class="simple-keyboard" style="max-width:500px; margin:auto; margin-top:3%"></div>

</template>


<style scoped>
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
</style>
<style>

.simple-keyboard.hg-theme-default.myTheme {
  border: 5px solid rgba(182, 47, 255, 0.7);
  background-color: rgba(133, 32, 187, 0.7);
  border-radius: 10px;
  margin: 10px;
  width: calc(100% - 20px);
}

.simple-keyboard.hg-layout-default .hg-button.hg-red {
  background: rgba(166, 35, 237, 0.7);
  color: white;
}

.miss {
  background: rgba(78, 78, 72, 0.7) !important;
  color: white;
}
.misplace {
  background: rgba(252, 218, 25, 0.7) !important;
  color: white;
}
.found {
  background: rgba(221, 30, 23, 0.7) !important;
  color: white;
}

</style>
