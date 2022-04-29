<script setup>
import Keyboard from 'simple-keyboard';
import 'simple-keyboard/build/css/index.css';
import {onMounted, ref, defineEmits, defineProps, watch} from 'vue';

const emit = defineEmits(["onKeyPress"]);

const keyboard = ref(null);

const props = defineProps({
  guessedletter: Object,
});

console.log(props.guessedletter)
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
    ]
  });
});

watch( () => props.guessedletter, (guessedletter) => {
  console.log("j'update le clavier")
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
